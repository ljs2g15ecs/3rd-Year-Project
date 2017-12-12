module test_SIMON_function;
parameter N = 16;
parameter M = 4;

logic [N-1:0] in, out;

SIMON_function f(.*);

initial
begin
	in = 16'h6565;
	#50ns	in = 16'h6877;
end

endmodule
