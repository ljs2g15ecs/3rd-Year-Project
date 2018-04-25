module SIMON_control_INL
#(
parameter			N =	16,
parameter			M =	4,
parameter			T =	32,
parameter			Cb =	5
)
(
input logic			clk, nR,
input logic			newData, readData,
input logic [2*N-1:0]		plain,
input logic [M-1:0][N-1:0]	key,
output logic			doneData, doneKey,
output logic [2*N-1:0]		cipher
);

//	STATE LOGIC
typedef enum {s0, s1, s2, s3} 	state;
state 				current, next;

logic [Cb-1:0]			count;

//	KEY EXPANSION LOGIC
logic [T-1:0][N-1:0]		keys;
logic [M-1:0][N-1:0] 		pKeys;
logic [N-1:0] 			out;

SIMON_keyexpansion k(.*);

//	ROUNDD FUNCTION LOGIC
logic [N-1:0] 			rKey;
logic [2*N-1:0] 		p, c;

assign rKey = doneKey ? keys[count] : pKeys[0];

SIMON_round r(.in(p), .key(rKey), . out(c) );

//assign cipher = doneData ? c : 'b0;

always_ff @(posedge clk or negedge nR)
begin
	if(~nR)
	begin
		current <= s0;
		count <= 'b0;
		doneData <= 1'b0;
		doneKey <= 1'b0;
		p <= 'b0;
		cipher <= 'b0;
		keys <= 'b0;
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
			p <= plain;
			count <= 'b0;
			doneData <= 1'b0;
		end
		s2:
		begin
			if(~doneKey)
			begin
				keys[count] <= rKey;
				pKeys <= {out, pKeys[M-1:1]};
			end
			p <= c;
			count <= count + 1'b1;
		end
		s3:
		begin
			cipher <= p;
			doneData <= 1'b1;
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
		if(newData)		next = s1;
		else			next = s0;
	end
	s1:				next = s2;
	s2:
	begin
		if(count != T-1)	next = s2;
		else			next = s3;
	end
	s3:
	begin
		if(readData)		next = s0;
		else			next = s3;
	end
	endcase
end

endmodule
