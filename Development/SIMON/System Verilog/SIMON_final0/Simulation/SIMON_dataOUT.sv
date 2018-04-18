module SIMON_dataOUT
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0			)
 (	input logic clk, nR,
	input logic readOUT,
	input logic doneData,
	input logic [7:0] infoOUT, countOUT,
	input logic [1:0][N-1:0] blockOUT,
	input logic [M-1:0][N-1:0] KEY,
	output logic newOUT, doneOUT,
	output logic readData,
	output logic [(1+(N/2)):0][7:0] out	);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, READ, WRITE} state;
state current, next;

logic				nBLOCK, LOADING;
logic [7:0] 			info, countPkt;
logic [3:0][N-1:0] 		data;

logic [(1+(N/2)):0][7:0] pkt;
assign pkt = {info, countOUT, data[3], data[2], data[1], data[0]};

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		newOUT <= 1'b0;
		doneOUT <= 1'b0;
		readData <= 1'b0;

		current <= WAIT;

		nBLOCK <= 1'b0;
		LOADING <= 1'b0;
		info <= 'b0;
		countPkt <= 'b0;
		data <= 'b0;

		out <= 'b0;
	end
	else
	begin
		if(doneOUT && readOUT)		doneOUT <= 1'b0;
		if(readData && ~doneData)	readData <= 1'b0;
		unique case(current)
		WAIT:
		begin
			if(next == READ)	nBLOCK <= 1'b0;
			//else			doneOUT <= 1'b1;
		end
		LOAD:
		begin
			LOADING <= 1'b1;

			info <= infoOUT;

			if(countOUT == countPkt)	countPkt <= countPkt + 1;
			else				$display("ERROR - PACKET COUNT TRACKER");
			
			if(infoOUT[3:0] != MODE)	$display("ERROR - INCORRECT MODE");
	
			if(~infoOUT[4])			$display("ERROR - INPUT PACKET");

			nBLOCK <= ~infoOUT[5] && infoOUT[7];
		end
		READ:
		begin
			readData <= 1'b1;
			if(infoOUT[5])
			begin
				//for(int i=0; i<M; i++)	data[i] <= KEY[i];
				data <= 'b0;
			end
			else
			begin
				data[{~nBLOCK, 1'b0}] <= blockOUT[0];
				data[{~nBLOCK, 1'b1}] <= blockOUT[1];
			end
		end
		WRITE:
		begin
			LOADING <= 1'b0;
			if(next == WAIT)
			begin
				doneOUT <= 1'b1;
				out <= pkt;
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
		if(LOADING && nBLOCK)
		begin
			if(doneData && readData)	next = WAIT;
			else if(doneData)		next = READ;
		end
		else if(~LOADING && doneData && ~doneOUT)		next = LOAD;
		else					next = WAIT;
	end
	LOAD:
	begin
		if(doneData)				next = READ;
		else					next = LOAD;
	end
	READ:
	begin
		if(nBLOCK)				next = WAIT;
		else					next = WRITE;
	end
	WRITE:
	begin
		if(doneOUT || readOUT)			next = WRITE;
		else					next = WAIT;
	end
	endcase
end

endmodule
