`include "SIMON_defintions.svh"

module SIMON_function
 (	input logic [`N-1:0] in,
	output logic [`N-1:0] out	);

always_comb
begin
	out = ({in[`N-2:0], in[`N-1]} & {in[`N-9:0], in[`N-1:`N-8]}) ^ {in[`N-3:0], in[`N-1:`N-2]};
end

endmodule
