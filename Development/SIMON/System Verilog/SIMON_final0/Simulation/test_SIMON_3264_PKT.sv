module test_SIMON_3264_PKT;

parameter N = 16;
parameter M = 4;
parameter T = 32;	
parameter Cb = 5;
parameter MODE = 0;

logic clk, nR;
logic newIN;
logic [(1+(N/2)):0][7:0] in;
logic loadPkt, donePkt;
logic [1:0][N-1:0] outData;

SIMON_3264_PKT S3264_PKT(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	@(posedge clk);

	nR = 1'b0;

	#10ns

	nR = 1'b1;
	newIN = 1'b0;

	in = 80'hE0001918111009080100;

	repeat(2)	@(posedge clk);
	#10ns

	newIN = 1'b1;

	repeat(32)	@(posedge clk);
	#10ns

	newIN = 1'b1;
end

always @(posedge loadPkt)
begin
	repeat(2)	@(posedge clk);
	#10ns

	newIN = 1'b0;

	repeat(2)	@(posedge clk);
	#10ns

	in = 80'hC0016565687721403F21;
end

/*
always @(posedge donePkt)
begin
	in = 80'hC0016565687721403F21;

	repeat(2)	@(posedge clk);
	#10ns

	newIN = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	newIN = 1'b0;
end
/*/

endmodule
