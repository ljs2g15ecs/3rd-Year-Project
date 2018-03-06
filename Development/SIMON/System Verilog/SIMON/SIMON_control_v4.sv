module SIMON_control_v4
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter C = 5			)
 (	input logic clk, nR,
	input logic newData, newKey,
	input logic enc_dec, readData,
	input logic [2*N-1:0] plain,
	input logic [M-1:0][N-1:0] key,
	output logic ldData, ldKey,
	output logic doneData, doneKey,
	output logic [2*N-1:0] cipher	);

logic [C-1:0] count;

//	STATES
typedef enum {s0, s1} state;
state current, next;

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0] pKeys;
logic [T-1:0][N-1:0] keys;
logic [N-1:0] oKey, rKey;
SIMON_keyexpansion ke(.count(count), .keys(pKeys), .out(oKey));
assign rKey = doneKey ? keys[count] : pKeys[0];

//	CIPHER LOGIC
logic [2*N-1:0] p, c;
SIMON_round r(.block(p), .key(rKey), .out(c));
assign cipher = doneData ? p : 'bZ;

logic clkCipherGo, clkCipher;
logic clkKeyGo, clkKey;

always_ff @(posedge newData)	ldData <= newData;

always_ff @(posedge newKey)	ldKey <= newKey;

always_ff @(posedge readData)	doneData <= 1'b0;

always_ff @(negedge clk)
begin
	if(current == s0)
	begin
		if(ldData)	doneData <= 1'b0;
		if(ldKey)	doneKey <= 1'b0;
		clkCipherGo <= (ldData && ~doneData) && (ldKey || doneKey);
		clkKeyGo <= ldKey;
	end
end

always_comb
begin	
	if(clkCipherGo)	clkCipher = clk;
	else		clkCipher = 1'b0;

	if(clkKeyGo)	clkKey = clk;
	else		clkKey = 1'b0;
end

//	MAIN
always_ff @(posedge clkCipher, posedge clkKey, negedge nR)
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
		endcase
		current <= next;
	end
end

//	CIPHER
always_ff @(posedge clkCipher, negedge nR)
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
			ldData <= 1'b0;
		end
		s1:
		begin
			p <= c;
		end
		endcase
	end
end

//	KEY
always_ff @(posedge clkKey, negedge nR)
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
			ldKey <= 1'b0;
		end
		s1:
		begin
			keys[count] <= pKeys[0];
			pKeys <= {oKey, pKeys[M-1:1]};
		end
		endcase
	end
end

//	NEXT STATE LOGIC
always_comb
begin
	unique case(current)
	s0:
	begin
		next = s1;
	end
	s1:
	begin
		if(count >= T-1)	next = s0;
	end
	endcase
end

endmodule
