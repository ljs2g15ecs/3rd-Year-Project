module test_SIMON_control;
parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter C = 5;

logic clk, nR, done, newData, newKey;
logic [C:0] count;
logic [2*N-1:0] plain;
logic [2*N-1:0] cipher;
logic [M-1:0][N-1:0] key;

SIMON_control c(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	nR = 1'b1;
	newData = 1'b0;

	plain = 32'h65656877;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;

	#4025ns	nR = 1'b0;
	#50ns	nR = 1'b1;

	#4000ns	newData = 1'b1;
	#75ns	newData = 1'b0;
end

endmodule
