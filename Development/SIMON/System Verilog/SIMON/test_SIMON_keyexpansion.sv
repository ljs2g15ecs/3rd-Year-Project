module test_SIMON_keyexpansion;
parameter N = 16;
parameter M = 4;

logic [M-1:0][N-1:0] keys;
logic [N-1:0]out;
int i;

SIMON_keyexpansion k(.count(i), .keys(keys), .out(out) );

initial
begin
	i = 0;
	keys[3] = 16'h1918;
	keys[2] = 16'h1110;
	keys[1] = 16'h0908;
	keys[0] = 16'h0100;

	#50ns
	keys[0] = keys[1];
	keys[1] = keys[2];
	keys[2] = keys[3];
	keys[3] = out;
	i++;

	#50ns
	keys[0] = keys[1];
	keys[1] = keys[2];
	keys[2] = keys[3];
	keys[3] = out;
	i++;

	#50ns
	keys[0] = keys[1];
	keys[1] = keys[2];
	keys[2] = keys[3];
	keys[3] = out;
	i++;
	
end

endmodule
