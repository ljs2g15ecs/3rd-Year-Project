module test_SIMON_control_1;
parameter N = 16;
parameter M = 4;
parameter T = 32;

logic clk, nReset;
logic enc_dec;
int count;
logic kLd, kExp, pLd;
logic done;
logic [2*N-1:0] plain;
logic [2*N-1:0] cipher;
logic [N-1:0] key[M-1:0];

SIMON_control_1 c(.*);

initial
begin
	clk = 1'b0;
	forever #50ns clk = ~clk;
end

initial
begin
	nReset = 1'b1;
	enc_dec = 1'b0;

	plain = 32'h65656877;
	//plain = 32'hC69BE9BB;

	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
end	

endmodule