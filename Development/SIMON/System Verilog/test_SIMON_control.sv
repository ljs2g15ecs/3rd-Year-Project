module test_SIMON_control;
parameter N = 16;
parameter M = 4;
parameter T = 32;

logic clk, nReset, done;
int count;
logic [2*N-1:0] plain;
logic [2*N-1:0] cipher;
logic [M-1:0][N-1:0] key;

SIMON_control c(.*);

initial
begin
	clk = 1'b0;
	forever #50ns clk = ~clk;
end

initial
begin
	nReset = 1'b1;

	plain = 32'h65656877;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
end

endmodule
