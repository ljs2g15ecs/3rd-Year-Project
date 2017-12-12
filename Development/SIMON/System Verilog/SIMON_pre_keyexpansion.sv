module SIMON_pre_keyexpansion
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32		)
 (	input logic clk, nReset,
	output logic done,
	input logic [N-1:0] key[M-1:0],
	output logic [N-1:0] keys[T-1:0]);

int count;

typedef enum {s0, s1, s2} state;
state current, next;

logic [N-1:0] tmp;
reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;

always_ff @(posedge clk, negedge nReset)
begin
	unique case(current)
	s0:
	begin
		foreach(key[i])	keys[i] <= key[i];
		count <= M;
	end
	s1:
	begin
		keys[count] <= tmp;
		count <= count + 1;
	end
	s2:
	begin
		
	end
	endcase
	current <= next;
end

always_comb
begin
	unique case(current)
	s0:
	begin
		next = s1;
		done = 0;
	end
	s1:
	begin
		tmp = {keys[count-1][2:0], keys[count-1][N-1:3]};
		if(M==4)
		begin
			tmp ^= keys[count-3];
		end
		tmp ^= {tmp[0], tmp[N-1:1]};
		tmp = ~keys[count-M] ^ tmp ^ z[(count-M)%62] ^ 3;

		if(count == T-1)
		begin
			done = 1;
			next = s2;
		end
	end
	s2:
	begin
		
	end
	endcase
end


endmodule
