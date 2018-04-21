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

logic [1:0][`N-1:0]		testDATA;
logic [7:0]			countPKT;

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
	testDATA = `in_DATA_TEST;
	countPKT = 8'h00;
	in = {`in_iKEY_TEST, countPKT, `in_KEY_TEST };

	@(posedge clk);
	#10ns

	nR = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns
	
	newPKT <= 1'b1;
end

always @(posedge loadPKT)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	countPKT <= countPKT + 1'b1;	
	newPKT <= 1'b0;
end

always @(posedge newDATA)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	loadDATA <= 1'b1;
end

always @(negedge newDATA)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	loadDATA <= 1'b0;
end

always @(posedge newKEY)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	loadKEY <= 1'b1;
end

always @(negedge newKEY)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	loadKEY <= 1'b0;
end

always @(posedge donePKT)
begin
	repeat(2)	@(posedge clk);
	#10ns

	in <= { `in_iDATA_TEST, countPKT, testDATA, ~testDATA};
	
	@(posedge clk)
	newPKT <= 1'b1;
	testDATA <= ~testDATA;
end

endmodule
