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
	output logic loadPkt, donePkt,
	output logic [7:0] info, infoCOUNT,
	output logic newKey, newData,
	output logic enc_dec,
	output logic [1:0][N-1:0] BLOCK,
	output logic [M-1:0][N-1:0] KEY		);

//	STATES
typedef enum bit [1:0] {LOAD, COMPUTE, WRITE, WAIT} state;
state current, next;

logic				nBLOCK;
logic [7:0] 			pktCOUNT;
logic [3:0][N-1:0] 		data;

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		pktCOUNT <= 'b0;

		info <= 'b0;
		infoCOUNT <= 'b0;
		
		newData <= 1'b0;
		newKey <= 1'b0;
		enc_dec <= 1'b0;

		BLOCK <= 'b0;
		KEY <= 'b0;

		loadPkt <= 1'b0;
		donePkt <= 1'b0;

		current <= WAIT;
	end
	else
	begin
		unique case(current)
		LOAD:
		begin
			data[0] <= in[(N/8)-1:0];
			data[1] <= in[(N/4)-1:(N/8)];
			data[2] <= in[(3*N/8)-1:(N/4)];
			data[3] <= in[(N/2)-1:(3*N/8)];

			infoCOUNT <= in[(N/2)];
			info <= in[(N/2)+1];

			loadPkt <= 1'b1;

			donePkt <= 1'b0;
		end
		COMPUTE:
		begin
			if(infoCOUNT == pktCOUNT)	pktCOUNT <= pktCOUNT + 1;
			else				//	ERROR - PACKET COUNT TRACKER
			
			if(info[3:0] != MODE)		//	ERROR - INCORRECT MODE
	
			if(info[4])			//	ERROR - OUTPUT PACKET
			
			enc_dec <= info[6];

			nBLOCK <= info[7];
		end
		WRITE:
		begin
			loadPkt <= 1'b0;

			if(info[5])
			begin
				newKey <= 1'b1;
				for(int i=0; i<M; i++)	KEY[i] <= data[i];
			end
			else
			begin
				newData <= 1'b1;
				BLOCK[0] <= data[{~nBLOCK, 1'b0}];
				BLOCK[1] <= data[{~nBLOCK, 1'b1}];
			end
		end
		WAIT:
		begin
			if(next == WRITE)	nBLOCK <= 1'b0;
			else if(loadData || loadKey)	donePkt <= 1'b1;
			if(newData && loadData)	newData <= 1'b0;
			if(newKey && loadKey)	newKey <= 1'b0;
		end
		endcase
		current <= next;
	end
end

always_comb
begin
	unique case(current)
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
	WAIT:
	begin
		if(loadData || loadKey)
		begin
			if(newData && nBLOCK)	next = WRITE;
			else			next = WAIT;
		end
		else if(newIN)			next = LOAD;
		else				next = WAIT;
	end
	endcase
end

endmodule
