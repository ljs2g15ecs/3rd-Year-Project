`include "SIMON_defintions.svh"

module SIMON_dataOUT
(	input logic				clk, nR,
	input logic				out_readPKT,
	input logic				doneDATA,
	input logic [7:0]			infoOUT, countOUT,
	input logic [1:0][`N-1:0]		outDATA,
	output logic 				out_donePKT,
	output logic 				readDATA,
	output logic [(1+(`N/2)):0][7:0]	out			);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, READ, WRITE} state;
state current, next;

logic						doneDATA_rise;

logic [(1+(`N/2)):0][7:0]			pkt;
logic						nBLOCK, PROCESSING;
logic [7:0] 					info, countPKT;
logic [3:0][`N-1:0] 				data;

assign pkt = {info, countPKT, data[3], data[2], data[1], data[0]};

always @(posedge doneDATA, posedge readDATA, negedge nR)
begin
	if(~nR)					doneDATA_rise <= 1'b0;
	else if(readDATA)			doneDATA_rise <= 1'b0;
	else if(doneDATA)			doneDATA_rise <= 1'b1;
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
		out_donePKT <= 1'b0;
		readDATA <= 1'b0;
		out <= 'b0;

		current <= WAIT;
	end
	else
	begin
		if(out_donePKT && out_readPKT)		out_donePKT <= 1'b0;		
		unique case(current)
		WAIT:
		begin
			readDATA <= 1'b0;
		end
		LOAD:
		begin
			PROCESSING <= 1'b1;			
			
			if(infoOUT[3:0] != `MODE)	$display("OUTPUT ERROR - INCORRECT MODE");
			if(~infoOUT[4])			$display("OUTPUT ERROR - INPUT PACKET");

			info <= infoOUT;
			nBLOCK <= ~infoOUT[5] && infoOUT[7];
		end
		READ:
		begin
			if(info[5])
			begin
				data <= 'b0;
			end
			else if(~info[5])
			begin
				data[{~nBLOCK, 1'b0}] <= outDATA[~info[6]];
				data[{~nBLOCK, 1'b1}] <= outDATA[info[6]];
				nBLOCK <= 1'b0;
			end
			
			readDATA <= 1'b1;
			
			if(~nBLOCK)	PROCESSING <= 1'b0;
		end
		WRITE:
		begin
			if(next == WAIT)
			begin
				out_donePKT <= 1'b1;
				countPKT <= countPKT + 1;
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
			if(PROCESSING)		next = READ;
			else			next = LOAD;
		end
		else				next = WAIT;
	end
	LOAD:
	begin
						next = READ;
	end
	READ:
	begin
		if(nBLOCK)			next = WAIT;
		else				next = WRITE;		
	end
	WRITE:
	begin
		if(out_donePKT || out_readPKT)		next = WRITE;
		else				next = WAIT;
	end
	endcase
end

endmodule
