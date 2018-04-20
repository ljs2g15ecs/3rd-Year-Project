`include "SIMON_defintions.svh"

module SIMON_dataOUT
(	input logic				clk, nR,
	input logic				readPKT,
	input logic				doneDATA,
	input logic [7:0]			infoOUT, countOUT,
	input logic [1:0][`N-1:0]		outDATA,
	output logic 				donePKT,
	output logic 				readDATA,
	output logic [(1+(`N/2)):0][7:0]	out			);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, READ, WRITE} state;
state current, next;

logic					doneDATA_rise;

logic [(1+(`N/2)):0][7:0]		pkt;
logic					nBLOCK, PROCESSING;
logic [7:0] 				info, countPKT;
logic [3:0][`N-1:0] 			data;

assign pkt = {info, countOUT, data[3], data[2], data[1], data[0]};

always @(posedge doneDATA, posedge readDATA, negedge nR)
begin
	if(~nR)				doneDATA_rise <= 1'b0;
	else if(readDATA)		doneDATA_rise <= 1'b0;
	else if(doneDATA)		doneDATA_rise <= 1'b1;
end

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		nBLOCK <= 1'b0;
		PROCESSING <= 1'b0;
		info <= 'b0;
		countPKT <= 'b0;
		data <= 'b0;
		donePKT <= 1'b0;
		readDATA <= 1'b0;
		out <= 'b0;

		current <= WAIT;
	end
	else
	begin
		if(donePKT && readPKT)	donePKT <= 1'b0;		
		unique case(current)
		WAIT:
		begin
			readDATA <= 1'b0;
		end
		LOAD:
		begin
			PROCESSING <= 1'b1;			
			
			if(countOUT != countPKT)	$display("ERROR - PACKET COUNT TRACKER");
			else if(infoOUT[3:0] != `MODE)	$display("ERROR - INCORRECT MODE");
			else if(~infoOUT[4])		$display("ERROR - OUTPUT PACKET");
			else
			begin
				countPKT <= countPKT + 1;
				info <= infoOUT;
				nBLOCK <= ~infoOUT[5] && infoOUT[7];
			end
		end
		READ:
		begin
			if(info[5] && doneDATA)
			begin
				data <= 'b0;
			end
			else if(~info[5] && doneDATA)
			begin
				readDATA <= 1'b1;
				data[{~nBLOCK, 1'b0}] <= outDATA[0];
				data[{~nBLOCK, 1'b1}] <= outDATA[1];
				nBLOCK <= 1'b0;
			end
			
			if(~nBLOCK)	PROCESSING <= 1'b0;
		end
		WRITE:
		begin
			if(next == WAIT)
			begin
				donePKT <= 1'b1;
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
		if(doneDATA_rise)
		begin
			if(PROCESSING)	next = READ;
			else		next = LOAD;
		end
		else			next = WAIT;
	end
	LOAD:
	begin
					next = READ;
	end
	READ:
	begin
		if(nBLOCK)		next = WAIT;
		else			next = WRITE;		
	end
	WRITE:
	begin
		if(donePKT || readPKT)	next = WRITE;
		else			next = WAIT;
	end
	endcase
end

endmodule