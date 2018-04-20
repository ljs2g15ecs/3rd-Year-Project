`include "SIMON_defintions.svh"

module test_SIMON_dataIN;

//	INPUTS
logic				clk, nR;
logic				newPKT;
logic				loadDATA, loadKEY;
logic [(1+(`N/2)):0][7:0]	in;

//	OUTPUTS
logic				loadPKT, donePKT;
logic				newKEY, newDATA;
logic [7:0]			infoIN, countIN;
logic [1:0][`N-1:0]		inDATA;
logic [`M-1:0][`N-1:0]		KEY;

SIMON_dataIN dIN(.*);

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

	newPKT = 1'b0;
	loadDATA = 1'b0;
	loadKEY = 1'b0;
	in = 'b0;

	@(posedge clk);
	#10ns

	nR = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns
	
	newPKT <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns
	
	newPKT <= 1'b0;
end

endmodule