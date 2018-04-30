`include "SIMON_defintions.svh"

module test_SIMON_128256_THROUGHPUT;

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

logic				encrypt, doneSIM;
int				countIN, countOUT, countCYCLE;

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

`define				PKT_MAX 2401
logic [`PKT_MAX:0][(1+(`N/2)):0][7:0]inPKT;

initial
begin
	nR = 1'b0;	
	@(posedge clk);
	#10ns
	
	in_newPKT = 1'b0;
	out_readPKT = 1'b0;
	encrypt = 1'b1;
	doneSIM = 1'b0;
	countIN = 0;
	countOUT = 0;
	countCYCLE = 0;

	in = inPKT[countIN];

	@(posedge clk);
	#10ns

	nR = 1'b1;

	@(posedge clk);
	#10ns
	
	in_newPKT <= 1'b1;
end

always @(posedge clk)				countCYCLE <= countCYCLE + 1'b1;

always @(posedge in_loadPKT)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	if(~doneSIM && (countIN != `PKT_MAX))	countIN <= countIN + 1'b1;
	else					doneSIM = 1'b1;
	in_newPKT <= 1'b0;
end

always @(posedge in_donePKT)
begin
	repeat(2)	@(posedge clk);
	#10ns

	if(~doneSIM)
	begin
		in = inPKT[countIN];
	
		@(posedge clk)
		in_newPKT <= 1'b1;
	end
end

always @(posedge out_donePKT)
begin
	if(countOUT != `PKT_MAX)		countOUT <= countOUT + 1'b1;
	else
	begin
		$display("%d PACKETS PROCESS AND FINISHED @ %tns in %d cycles", countOUT, $time, countCYCLE);
	end

	repeat(2)	@(posedge clk);
	#10ns
	
	out_readPKT <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	out_readPKT <= 1'b0;
end

endmodule
