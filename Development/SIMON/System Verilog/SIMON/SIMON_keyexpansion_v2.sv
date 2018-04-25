module SIMON_keyexpansion_v2
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter C = 5			)
 (	input logic clk, nR,
	input logic newKey,
	input logic [C-1:0] count,
	input logic [M-1:0][N-1:0] key,
	output logic ldKey, doneKey,
	output logic [N-1:0] rKey	);

logic [T-1:0][N-1:0] keys;
logic [M-1:0][N-1:0] pKeys;
logic [N-1:0] out;

typedef enum {s0, s1, s2, s3} state;
state current, next;

assign rKey = doneKey ? keys[count] : pKeys[0];
//assign ldKey = (current == s0 & newKey) ? 1'b1 : 1'b0;

always_ff @(posedge newKey)
begin
	ldKey <= 1'b1;
end

logic gateClk;
assign gateClk = ~doneKey & clk;

always_ff @(posedge gateClk or negedge nR)
begin
	if(~nR)
	begin
	end
	else
	begin
		unique case(current)
		s0:
		begin
			//count <= 0;
			foreach(key[i])	pKeys[i] <= key[i];
			if(newKey)	ldKey <= 1'b0;
		end
		s1:
		begin
			keys[count] <= pKeys[0];
			pKeys <= {out, pKeys[M-1:1]};
			//count <= count + 1;
		end
		s2:
		begin
		end
		s3:
		begin
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
		if(newKey)
		begin
			next = s1;
			doneKey = 1'b0;
		end
	end
	s1:
	begin
		if(count < T-1)	next = s1;
		else		next = s2;
	end
	s2:
	begin
		next = s0;
		if(newKey)	doneKey = 1'b0;
		else		doneKey = 1'b1;
	end
	s3:
	begin
	end
	endcase
end

reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;

always_comb
begin
	out = {pKeys[M-1][2:0], pKeys[M-1][N-1:3]};
if(M==4)
begin
	out ^= pKeys[M-3];
end
	out ^= {out[0], out[N-1:1]};
	out ^= ~pKeys[0] ^ z[count] ^ 3;
end

endmodule
