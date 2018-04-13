module SIMON_dataIN
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0			)
 (	input logic clk, nR,
	input logic newIN,
	input logic [(1+(N/2)):0][7:0] in,
	input logic loadData, loadKey,
	input logic doneData, doneKey,
	output logic loadPkt, donePkt,
	output logic [7:0] infoIN, countIN,
	output logic newKey, newData,
	output logic enc_dec,
	output logic [1:0][N-1:0] blockIN,
	output logic [M-1:0][N-1:0] KEY		);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, COMPUTE, WRITE} state;
state current, next;

logic				nBLOCK;
logic [7:0] 			countPkt;
logic [3:0][N-1:0] 		data;

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		countPkt <= 'b0;

		infoIN <= 'b0;
		countIN <= 'b0;
		
		newData <= 1'b0;
		newKey <= 1'b0;
		enc_dec <= 1'b0;
		nBLOCK <= 1'b0;

		blockIN <= 'b0;
		KEY <= 'b0;

		loadPkt <= 1'b0;
		donePkt <= 1'b1;

		current <= WAIT;
	end
	else
	begin
		if(newData && loadData)	newData <= 1'b0;
		if(newKey && loadKey)	newKey <= 1'b0;
		unique case(current)
		WAIT:
		begin
			if(next == WRITE)		nBLOCK <= 1'b0;
			else if(doneData || doneKey)	donePkt <= 1'b1;
		end
		LOAD:
		begin
			if(donePkt)
			begin
				data[0] <= in[(N/8)-1:0];
				data[1] <= in[(N/4)-1:(N/8)];
				data[2] <= in[(3*N/8)-1:(N/4)];
				data[3] <= in[(N/2)-1:(3*N/8)];

				countIN <= in[(N/2)];
				infoIN <= in[(N/2)+1];

				loadPkt <= 1'b1;

				donePkt <= 1'b0;
			end
		end
		COMPUTE:
		begin
			if(countIN == countPkt)		countPkt <= countPkt + 1;
			else				$display("ERROR - PACKET COUNT TRACKER");
			
			if(infoIN[3:0] != MODE)		$display("ERROR - INCORRECT MODE");
	
			if(infoIN[4])			$display("ERROR - OUTPUT PACKET");
			
			enc_dec <= infoIN[6];

			nBLOCK <= ~infoIN[5] && infoIN[7];
		end
		WRITE:
		begin
			loadPkt <= 1'b0;

			if(infoIN[5])
			begin
				newKey <= 1'b1;
				for(int i=0; i<M; i++)	KEY[i] <= data[i];
			end
			else
			begin
				newData <= 1'b1;
				blockIN[0] <= data[{~nBLOCK, 1'b0}];
				blockIN[1] <= data[{~nBLOCK, 1'b1}];
			end
		end
		endcase
		current <= next;
	end
end

always_comb
begin
	unique case(current)
	WAIT:
	begin
		if(nBLOCK)
		begin
			if(doneData)	next = WRITE;
			else		next = WAIT;
		end
		else if(newIN && donePkt)		next = LOAD;
	end
	LOAD:
	begin
		if(newIN)	next = COMPUTE;
		else		next = LOAD;
	end
	COMPUTE:
	begin
		next = WRITE;
	end
	WRITE:
	begin
		next = WAIT;
	end
	endcase
end

endmodule
