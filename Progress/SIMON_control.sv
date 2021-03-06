module SIMON_control
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32		)
 (	input logic clk,
	output int count,
	output logic done,
	input logic [2*N-1:0] plain,
	output logic [2*N-1:0] cipher,
	input logic [M-1:0][N-1:0] key	);

logic [M-1:0][N-1:0] keys;
logic [N-1:0] out;
SIMON_keyexpansion k(.*);
logic [2*N-1:0] p, c;
SIMON_round r(.block(p), .key(keys[0]), . out(c) );

typedef enum {s0, s1, s2} state;
state current, next;

always_ff @(posedge clk)
begin
	unique case(current)
		s0:
		begin
			keys <= key;
			p <= plain;
			count <= 0;
			done <= 0;
		end
		s1:
		begin
			keys <= {out, keys[M-1:1]};
			p <= c;
			count <= count + 1;
		end
		s2:
		begin
			done <= 1;
		end
	endcase
	current <= next;
end

always_comb
begin
	unique case(current)
		s0:
		begin
			//done = 1'b0;
			next = s1;
		end
		s1:
		begin
			if(count == T-2)	next = s2;
			else					next = s1;
		end
		s2:
		begin
			//done = 1'b1;
			next = s2;
		end
	endcase
end

assign cipher = done ? c : 0;


endmodule
