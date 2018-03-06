module SIMON_keyexpansion
#(	parameter N = 16,
	parameter M = 4,		
	parameter Co = 5			)
 (	input logic [Co-1:0] count,
	input logic [M-1:0][N-1:0] keys,
	input logic [61:0] z,
	output logic [N-1:0] out		);

always_comb
begin
	out = {keys[M-1][2:0], keys[M-1][N-1:3]};
if(M==4)
begin
	out ^= keys[M-3];
end
	out ^= {out[0], out[N-1:1]};
	out ^= ~keys[0] ^ z[count%62] ^ 16'd3;
end

endmodule