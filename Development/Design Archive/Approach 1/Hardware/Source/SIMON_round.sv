module SIMON_round
#(
parameter 		N = 	16,
parameter 		M = 	4	
)
(
input logic [2*N-1:0] 	in,
input logic [N-1:0] 	key,	
output logic [2*N-1:0]	out
);


logic [N-1:0] f, tmp;

SIMON_function func(.in(in[2*N-1:N]), .out(f));

always_comb
begin
	out[N-1:0] <= in[2*N-1:N];
	out[2*N-1:N] <= in[N-1:0] ^ key ^ f;
end

endmodule