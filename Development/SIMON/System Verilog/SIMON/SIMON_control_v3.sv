module SIMON_control_v3
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter C = 5			)
 (	input logic clk, nR,
	input logic newData, newKey,
	output logic ldData, ldKey,
	output logic doneData, doneKey, 
	input logic [2*N-1:0] plain,
	output logic [2*N-1:0] cipher,
	input logic [M-1:0][N-1:0] key	);

logic [C-1:0] count;

logic gateClkKey;
assign gateClkKey = ~doneKey & clk;

logic gateClkCipher;
assign gateClkCipher = ~doneData & clk;

typedef enum {s0, s1, s2, s3} state;
state current, next;

logic [M-1:0][N-1:0] pKeys;
logic [T-1:0][N-1:0] keys;
logic [N-1:0] oKey, rKey;
SIMON_keyexpansion ke(.count(count), .keys(pKeys), .out(oKey));

assign rKey = doneKey ? keys[count] : pKeys[0];

logic [2*N-1:0] p, c;
SIMON_round r(.block(p), .key(rKey), .out(c));

assign cipher = (next == s3) ? c : 'bZ;

always_ff @(posedge newData)
begin
	ldData <= 1'b1;
end

always_ff @(posedge newKey)
begin
	ldKey <= 1'b1;
end

always_ff @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
	end
	else
	begin
		unique case(current)
		s0:
		begin
			count <= 0;
		end
		s1:
		begin
			count <= count + 1;
		end
		s2:
		begin
		end
		s3:
		begin
		end
		endcase
	end
	current <= next;
end

always_ff @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
	end
	else
	begin
		unique case(current)
		s0:
		begin
			foreach(key[i])	pKeys[i] <= key[i];
			if(newKey)	ldKey <= 1'b0;
		end
		s1:
		begin
			keys[count] <= pKeys[0];
			pKeys <= {oKey, pKeys[M-1:1]};
		end
		s2:
		begin
		end
		s3:
		begin
		end
		endcase
	end
end

always_ff @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
	end
	else
	begin
		unique case(current)
		s0:
		begin
			p <= plain;
			if(newData)	ldData <= 1'b0;
		end
		s1:
		begin
			p <= c;
		end
		s2:
		begin
		end
		s3:
		begin
		end
		endcase
	end
end

always_comb
begin
	unique case(current)
	s0:
	begin
		if(newData)	doneData = 1'b0;
		if(newKey)	doneKey = 1'b0;

		if(newData & (newKey | doneKey))	next = s1;
	end
	s1:
	begin
		if(count < T-1)	next = s1;
		else		next = s3;
	end
	s2:
	begin
	end
	s3:
	begin
		next = s0;
		if(newData)	doneData = 1'b0;
		else		doneData = 1'b1;
		if(newKey)	doneKey = 1'b0;
		else		doneKey = 1'b1;
	end
	endcase
end

endmodule
