module SIMON_keyexpansion
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Co = 5			)
 (	input logic [Co-1:0] count,
	input logic [M-1:0][N-1:0] keys,
	output logic [N-1:0] out	);

//logic [N-1:0] tmp;
reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;

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