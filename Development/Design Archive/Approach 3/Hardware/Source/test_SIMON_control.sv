`include "SIMON_defintions.svh"

module test_SIMON_control;

//	INPUTS
logic 			clk, nR;
logic 			newDATA, newKEY;
logic 			readDATA;
logic [7:0]		infoIN, countIN;
logic [1:0][`N-1:0]	inDATA;
logic [`M-1:0][`N-1:0]	KEY;

//	OUPUTS
logic			newDATA_rise, newKEY_rise;
logic			loadDATA, loadKEY;
logic			doneDATA, doneKEY;
logic [7:0]		infoOUT, countOUT;
logic [1:0][`N-1:0]	outDATA;

SIMON_control control(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	nR = 1'b0;	
	@(posedge clk);
	#10ns
	
	newDATA = 1'b0;
	newKEY = 1'b0;
	readDATA = 1'b0;
	infoIN = `in_iDEC_TEST;
	countIN = 'b0;
	inDATA = `in_DEC_TEST;
	KEY = `in_KEY_TEST;	

	@(posedge clk);
	#10ns

	nR = 1'b1;

	@(posedge clk);
	#10ns
	
	newKEY <= 1'b1;
end

always @(posedge loadDATA)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	newDATA <= 1'b0;
end

always @(posedge loadKEY)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	newKEY <= 1'b0;
end

always @(posedge doneDATA)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	readDATA <= 1'b1;	

	repeat(2)	@(posedge clk);
	#10ns
	
	readDATA <= 1'b0;

	repeat(2)	@(posedge clk);
	#10ns
	
	newDATA <= 1'b1;
end

endmodule