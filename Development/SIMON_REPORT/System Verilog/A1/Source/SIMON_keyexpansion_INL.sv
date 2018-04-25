module SIMON_keyexpansion_INL
#(
parameter 			N = 	16,
parameter 			M = 	4,
parameter 			T = 	32,		
parameter 			Cb = 	5
)
(
input logic [Cb-1:0]		count,
input logic [M-1:0][N-1:0]	pKeys,
output logic [N-1:0]		out
);

//logic [N-1:0] tmp;
reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;

always_comb
begin
	out = {pKeys[M-1][2:0], pKeys[M-1][N-1:3]};
if(M==4)
begin
	out ^= pKeys[M-3];
end
	out ^= {out[0], out[N-1:1]};
	out ^= ~pKeys[0] ^ z[count%62] ^ 16'd3;
end

endmodule
