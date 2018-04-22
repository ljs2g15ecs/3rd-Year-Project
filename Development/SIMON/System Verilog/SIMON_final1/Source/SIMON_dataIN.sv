`include "SIMON_defintions.svh"

module SIMON_dataIN
(	input logic			clk, nR,
	input logic			in_newPKT,
	input logic			loadDATA, loadKEY,
	input logic [(1+(`N/2)):0][7:0]	in,
	output logic			in_loadPKT, in_donePKT,
	output logic			newKEY, newDATA,
	output logic [7:0]		infoIN, countIN,
	output logic [1:0][`N-1:0]	inDATA,
	output logic [`M-1:0][`N-1:0]	KEY			);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, COMPUTE, WRITE} state;
state current, next;

logic					newPKT_rise;

logic [(1+(`N/2)):0][7:0] 		pkt;
logic					nBLOCK, PROCESSING;
logic [7:0] 				info, countPKT;
logic [3:0][`N-1:0] 			data;

assign data[0] = 			pkt[(`N/8)-1:0];
assign data[1] = 			pkt[(`N/4)-1:(`N/8)];
assign data[2] = 			pkt[(3*`N/8)-1:(`N/4)];
assign data[3] = 			pkt[(`N/2)-1:(3*`N/8)];
assign countIN = 			pkt[(`N/2)];
assign info = 				pkt[(`N/2)+1];

always @(posedge in_newPKT, posedge in_loadPKT, negedge nR)
begin
	if(~nR)				newPKT_rise <= 1'b0;
	else if(in_loadPKT)		newPKT_rise <= 1'b0;
	else if(in_newPKT)		newPKT_rise <= 1'b1;
end

always @(PROCESSING, negedge nR)
begin
	if(~nR)				in_donePKT <= 1'b0;
	else if(PROCESSING)		in_donePKT <= 1'b0;
	else				in_donePKT <= 1'b1;
end

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		pkt <= 'b0;
		nBLOCK <= 1'b0;
		PROCESSING <= 1'b0;
		infoIN <= 1'b0;
		countPKT <= 'b0;

		in_loadPKT <= 1'b0;
		newDATA <= 1'b0;
		newKEY <= 1'b0;
		inDATA <= 'b0;
		KEY <= 'b0;
	
		current <= WAIT;
	end
	else
	begin
		if(newDATA && loadDATA)	newDATA <= 1'b0;
		if(newKEY && loadKEY)	newKEY <= 1'b0;
		unique case(current)
		WAIT:
		begin
			in_loadPKT <= 1'b0;
		end
		LOAD:
		begin
			pkt <= in;
			in_loadPKT <= 1'b1;
			PROCESSING <= 1'b1;
		end
		COMPUTE:
		begin
			if(countIN != countPKT)		$display("ERROR - PACKET COUNT TRACKER");
			else if(info[3:0] != `MODE)	$display("ERROR - INCORRECT MODE");
			else if(info[4])		$display("ERROR - OUTPUT PACKET");
			else
			begin
				countPKT <= countPKT + 1;
				nBLOCK <= ~info[5] && info[7];
			end
		end
		WRITE:
		begin
			if(info[5] && ~loadKEY)
			begin
				newKEY <= 1'b1;
				for(int i=0; i<`M; i++)	KEY[i] <= data[i];
			end
			else if(~info[5] && ~loadDATA)
			begin
				newDATA <= 1'b1;
				inDATA[0] <= data[{~nBLOCK, 1'b0}];
				inDATA[1] <= data[{~nBLOCK, 1'b1}];
				nBLOCK <= 1'b0;
			end

			infoIN <= info;

			if(~nBLOCK)	PROCESSING <= 1'b0;
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
		if(PROCESSING)
		begin
			if(newDATA || loadDATA)		next = WAIT;	
			else				next = WRITE;	
		end
		else
		begin
			if(newPKT_rise)			next = LOAD;
			else				next = WAIT;
		end
	end
	LOAD:						next = COMPUTE;
	COMPUTE:					next = WRITE;
	WRITE:						next = WAIT;
	endcase
end

endmodule
