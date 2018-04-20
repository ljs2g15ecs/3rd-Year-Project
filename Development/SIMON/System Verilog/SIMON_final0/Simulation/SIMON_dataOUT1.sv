module SIMON_dataOUT1
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
	output logic doneOUT,
	output logic readData,
	output logic [(1+(N/2)):0][7:0] out	);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, READ, WRITE} state;
state current, next;

logic				doneData_rise;

logic [(1+(N/2)):0][7:0]	pkt;
logic				nBLOCK, PROCESSING;
logic [7:0] 			info, countPkt;
logic [3:0][N-1:0] 		data;

assign pkt = {info, countOUT, data[3], data[2], data[1], data[0]};

always @(posedge doneData, posedge readData, negedge nR)
begin
	if(~nR)			doneData_rise <= 1'b0;
	else if(readData)	doneData_rise <= 1'b0;
	else if(doneData)	doneData_rise <= 1'b1;
end

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		nBLOCK <= 1'b0;
		PROCESSING <= 1'b0;
		info <= 'b0;
		countPkt <= 'b0;
		data <= 'b0;
		doneOUT <= 1'b0;
		readData <= 1'b0;
		out <= 'b0;

		current <= WAIT;
	end
	else
	begin
		if(doneOUT && readOUT)			doneOUT <= 1'b0;		
		unique case(current)
		WAIT:
		begin
			readData <= 1'b0;
		end
		LOAD:
		begin
			PROCESSING <= 1'b1;			
			
			if(countOUT != countPkt)	$display("ERROR - PACKET COUNT TRACKER");
			else if(infoOUT[3:0] != MODE)	$display("ERROR - INCORRECT MODE");
			else if(~infoOUT[4])		$display("ERROR - OUTPUT PACKET");
			else
			begin
				countPkt <= countPkt + 1;
				info <= infoOUT;
				nBLOCK <= ~infoOUT[5] && infoOUT[7];
			end
		end
		READ:
		begin
			if(info[5] && doneData)
			begin
				data <= 'b0;
			end
			else if(~info[5] && doneData)
			begin
				readData <= 1'b1;
				data[{~nBLOCK, 1'b0}] <= blockOUT[0];
				data[{~nBLOCK, 1'b1}] <= blockOUT[1];
				nBLOCK <= 1'b0;
			end
			
			if(~nBLOCK)			PROCESSING <= 1'b0;
		end
		WRITE:
		begin
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
		if(doneData_rise)
		begin
			if(PROCESSING)			next = READ;
			else				next = LOAD;
		end
		else					next = WAIT;
	end
	LOAD:
	begin
		next = READ;
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
