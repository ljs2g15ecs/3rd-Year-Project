`include "SIMON_defintions.svh"

module test_SIMON_topPKT;

//	INPUTS
logic				clk, nR;
logic				in_newPKT;
logic				out_readPKT;
logic [(1+(`N/2)):0][7:0]	in;

//	OUTPUTS
logic 				in_loadPKT, in_donePKT;
logic				out_donePKT;
logic [(1+(`N/2)):0][7:0]	out;

SIMON_topPKT			topPKT(.*);

logic				encrypted;
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
	
	in_newPKT = 1'b0;
	out_readPKT = 1'b0;
	encrypted = 1'b1;
	testDATA = `in_DATA_TEST;
	countPKT = 8'h00;
	in = {`in_iKEY_TEST, 8'h00, `in_KEY_TEST };

	@(posedge clk);
	#10ns

	nR = 1'b1;

	@(posedge clk);
	#10ns
	
	in_newPKT <= 1'b1;
end

always @(posedge in_loadPKT)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	if(encrypted)	countPKT <= countPKT + 1'b1;
	in_newPKT <= 1'b0;
end

always @(posedge in_donePKT)
begin
	repeat(2)	@(posedge clk);
	#10ns

	if(encrypted)
	begin
		in <= { `in_iDATA_TEST, countPKT, testDATA, testDATA};
	
		@(posedge clk)
		in_newPKT <= 1'b1;
		encrypted <= 1'b0;
	end
end

always @(posedge out_donePKT)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	out_readPKT <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	out_readPKT <= 1'b0;
end

endmodule
