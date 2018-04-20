`include "SIMON_defintions.svh"

module SIMON_keyexpansion
 (	input logic [`Cb-1:0] count,
	input logic [`M-1:0][`N-1:0] keys,
	output logic [`N-1:0] out		);

`ifdef J0
	const reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;
`else `ifdef J1
	const reg [61:0] z = 62'b01011010000110010011111011100010101101000011001001111101110001;
`else `ifdef J2
	const reg [61:0] z = 62'b11001101101001111110001000010100011001001011000000111011110101;
`else `ifdef J3
	const reg [61:0] z = 62'b11110000101100111001010001001000000111101001100011010111011011;
`else `ifdef J4
	const reg [61:0] z = 62'b11110111001001010011000011101000000100011011010110011110001011;
`endif
`endif
`endif
`endif
`endif

always_comb
begin
	out = {keys[`M-1][2:0], keys[`M-1][`N-1:3]};

	`ifdef M4
	out ^= keys[`M-3];
	`endif

	out ^= {out[0], out[`N-1:1]};
	out ^= ~keys[0] ^ z[count%62] ^ 16'd3;
end

endmodule
