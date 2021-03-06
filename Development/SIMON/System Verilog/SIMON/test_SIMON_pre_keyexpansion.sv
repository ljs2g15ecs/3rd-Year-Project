module test_SIMON_pre_keyexpansion;
parameter N = 16;
parameter M = 4;
parameter T = 32;

logic clk, nReset;
logic done;
logic [N-1:0] key[M-1:0];
logic [N-1:0] keys[T-1:0];

SIMON_pre_keyexpansion k(.*);

initial
begin
	clk = 1'b0;
	forever #50ns clk = ~clk;
end

initial
begin
	nReset = 1'b1;

	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
end

endmodule
