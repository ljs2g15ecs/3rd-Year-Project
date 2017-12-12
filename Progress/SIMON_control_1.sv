module SIMON_control_1
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32		)
 (	input logic clk, nReset,
	input logic enc_dec,
	output int count,
	output logic kLd, kExp, pLd,
	output logic done,
	input logic [2*N-1:0] plain,
	output logic [2*N-1:0] cipher,
	input logic [N-1:0] key[M-1:0]	);

logic [N-1:0] keys[T-1:0];
SIMON_pre_keyexpansion k(.clk(clk), .nReset(nReset), .done(kExp), .key(key),  .keys(keys));

logic [N-1:0] rKey;
logic [2*N-1:0] p, c;
SIMON_round r(.block(p), .key(rKey), . out(c) );

typedef enum {s0, s1, s2, s3} state;
state current, next;

always_ff @(posedge clk, negedge nReset)
begin
	unique case(current)
	s0:
	begin
		count <= 0;
		if(!enc_dec)		p <= plain;
		else			p <= {plain[N-1:0], plain[2*N-1:N]};
	end
	s1:
	begin
		rKey <= keys[count];
		if(count != 0)		p <= c;
		count <= count + 1;
	end
	s2:
	begin
		rKey <= keys[T-(count+1)];
		if(count != 0)	p <= c;
		count <= count + 1;
	end
	s3:
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
		kLd = 1;
		pLd = 1;
		done = 0;
		if(kExp)
		begin
			if(enc_dec)	next = s2;
			else		next = s1;
		end
	end
	s1:
	begin
		if(count == T-1)	next = s3;
	end
	s2:
	begin
		if(count == T-1)	next = s3;
	end
	s3:
	begin
		done = 1;
	end
	endcase
end

//assign cipher = (done & !enc_dec) ? c : 0;
assign cipher = (enc_dec) ? {c[N-1:0], c[2*N-1:N]} : c;

endmodule
