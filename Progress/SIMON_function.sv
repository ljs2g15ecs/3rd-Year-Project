module SIMON_function
#(	parameter N = 16,
	parameter M = 4			)
 (	input logic [N-1:0] in,
	output logic [N-1:0] out	);

logic [N-1:0] A, B, C;
///*
always_comb
begin
	A = {in[N-2:0], in[N-1]};
	B = {in[N-9:0], in[N-1:N-8]};
	C = {in[N-3:0], in[N-1:N-2]};
end
//*/
///*
always_comb
begin
	out = (A & B) ^ C;
end
//*/

endmodule
