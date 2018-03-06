module test_SIMON_keyexpansion_v2;
parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter C = 5;

logic clk, nR;
logic newKey;
logic [C:0] count;
logic [M-1:0][N-1:0] key;
logic ldKey, doneKey;
logic [N-1:0] rKey;

SIMON_keyexpansion_v2 ke(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns 	clk = ~clk;
end

initial
begin
	nR = 1'b1;

	key[3] = 16'h0000;
	key[2] = 16'h0000;
	key[1] = 16'h0000;
	key[0] = 16'h0000;

	#1000ns	newKey = 1'b1;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
	#200ns	newKey = 1'b0;

	#1800ns	newKey = 1'b1;
	key[3] = 16'h0000;
	key[2] = 16'h0000;
	key[1] = 16'h0000;
	key[0] = 16'h0000;
	#2200ns	newKey = 1'b0;

	#1000ns	newKey = 1'b1;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
	#2200ns	newKey = 1'b0;

	#4000ns	newKey = 1'b1;
	#200ns	newKey = 1'b0;
end

endmodule
