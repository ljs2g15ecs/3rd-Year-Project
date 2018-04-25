module test_SIMON_control_INL;

parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter C = 5;

logic clk, nR;
logic newData, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;

logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_control_INL c(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	nR = 1'b0;

	@(posedge clk)
	#10ns

	newData = 1'b0;
	readData = 1'b0;
	plain = 32'h65656877;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;

	@(posedge clk)
	#10ns

	nR = 1'b1;

	@(posedge clk)
	#10ns

	newData = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	newData = 1'b0;

	@(posedge doneData);

	repeat(2)	@(posedge clk);
	#10ns

	readData = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	readData = 1'b0;
	
	repeat(2)	@(posedge clk)
	#10ns

	newData = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	newData = 1'b0;
end

endmodule
