module test_SIMON_round;
parameter N = 16;
parameter M = 4;

logic [2*N-1:0] block, out;
logic [N-1:0] key;

SIMON_round r(.*);

initial
begin
	block = 32'h65656877;
	key = 16'h0100;

	#50ns
	block = out;
	key = 16'h0908;

	#50ns
	block = out;
	key = 16'h1110;
end

endmodule
