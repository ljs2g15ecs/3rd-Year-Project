`include "SIMON_defintions.svh"

module SIMON_round
 (	input logic [1:0][`N-1:0] in,
	input logic [`N-1:0] key,	
	output logic [1:0][`N-1:0] out	);

logic [`N-1:0] f;

SIMON_function func(.in(in[1]), .out(f));

always_comb
begin
	out[0] = in[1];
	out[1] = in[0] ^ key ^ f;
end

endmodule
