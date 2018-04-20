`include "SIMON_defintions.svh"

module test_SIMON_dataOUT;

//	INPUT
logic				clk, nR;
logic				readPKT;
logic				doneDATA;
logic [7:0]			infoOUT, countOUT;
logic [1:0][`N-1:0]		outDATA;

//	OUTPUT
logic 				donePKT;
logic 				readDATA;
logic [(1+(`N/2)):0][7:0]	out;

SIMON_dataOUT dOUT(.*);

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

	readPKT = 1'b0;
	doneDATA = 1'b0;
	infoOUT = 'b0;
	countOUT = 'b0;
	outDATA = 'b0;

	@(posedge clk);
	#10ns

	nR = 1'b1;

	/*
	repeat(2)	@(posedge clk);
	#10ns
	
	newPKT <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns
	
	newPKT <= 1'b0;
	//*/
end

endmodule
