module SIMON_keyexpansion_PRE
#(
parameter			N =	16,
parameter			M =	4,
parameter			T =	32,
parameter			Cb =	5
)
(
input logic			clk, nR,
input logic			newData,
input logic [M-1:0][N-1:0]	key,
output logic			doneKey,
output logic [T-1:0][N-1:0]	keys
);

//	STATE LOGIC
typedef enum {s0, s1, s2, s3} 	state;
state 				current, next;

logic [Cb-1:0]			count;

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0] 		pKeys;
logic [N-1:0] 			out;

SIMON_keyexpansion_INL 		k(.*);

always_ff @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		doneKey <= 1'b0;
		keys <= 'b0;
		current <= s0;
		pKeys <= 'b0;
	end
	else
	begin
		unique case(current)
		s0:
		begin
		end
		s1:
		begin
			pKeys <= key;
			count <= 'b0;
		end
		s2:
		begin
			if(~doneKey)
			begin
					keys[count] <= pKeys[0];
					pKeys <= {out, pKeys[M-1:1]};
			end
			count <= count + 1'b1;
		end
		s3:
		begin
			doneKey <= 1'b1;
		end
		endcase
		current <= next;
	end
end

always_comb
begin
	unique case(current)
	s0:
	begin
		if(newData && ~doneKey)	next = s1;
		else			next = s0;
	end
	s1:				next = s2;
	s2:
	begin
		if(count != T-1)	next = s2;
		else			next = s3;
	end
	s3:				next = s0;
	endcase
end

endmodule
