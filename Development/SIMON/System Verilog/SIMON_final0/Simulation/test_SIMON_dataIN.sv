module test_SIMON_dataIN;
parameter N = 16;
parameter M = 4;
parameter T = 32;	
parameter Cb = 5;
parameter MODE = 0;			

logic clk, nR;
logic newIN;
logic [(1+(N/2)):0][7:0] in;
logic loadData, loadKey;
logic loadPkt;
logic [7:0] info, infoCOUNT;
logic newKey, newData;
logic enc_dec;
logic [1:0][N-1:0] BLOCK;
logic [M-1:0][N-1:0] KEY;

SIMON_dataIN dIN(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	repeat(2)	@(posedge clk);

	nR = 1'b0;

	#10ns

	nR = 1'b1;
	newIN = 1'b0;

	loadData = 1'b0;
	loadKey = 1'b0;

	in = 80'h80006565687721403F21;

	repeat(2)	@(posedge clk);
	#10ns

	newIN = 1'b1;
end

always @(posedge loadPkt)
begin
	@(posedge clk);
	#10ns

	newIN <= 1'b0;
end

always @(posedge newData, posedge newKey)
begin
	repeat(2)	@(posedge clk);
	#10ns

	loadData <= newData;
	loadKey <= newKey;

	repeat(1)	@(posedge clk);
	#10ns

	loadData <= 1'b0;
	loadKey <= 1'b0;
end


endmodule
