module SIMON_control
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Co = 5			)
 (	input logic clk, nR,
	input logic newData, newKey,
	input logic enc_dec, readData,
	input logic [2*N-1:0] plain,
	input logic [M-1:0][N-1:0] key,
	input logic [N-1:0] oKey,
	output logic ldData, ldKey,
	output logic doneData, doneKey,
	output logic [2*N-1:0] cipher,
	output logic [M-1:0][N-1:0] pKeys,
	output logic [Co-1:0] count		);

//	STATES
typedef enum [1:0] {INIT, LOAD, EXECUTE, WRITE} state;
state current, next;

//	KEY EXPANSION LOGIC
logic [T-1:0][N-1:0] keys;
logic [N-1:0] rKey;

//	CIPHER LOGIC
logic [2*N-1:0] p, c;
SIMON_round #(N) r(.block(p), .key(rKey), .out(c));

//	GATED CLOCK LOGIC
logic clkCipherGo, clkCipher;
logic clkKeyGo, clkKey, clkAll;

assign clkCipher = clk && clkCipherGo;
assign clkKey = clk && clkKeyGo;
assign clkAll = clkCipher || clkKey;

logic ENCDEC;
assign rKey = ENCDEC ? keys[count] : keys[T-(count+1)];

always_ff @(negedge clk, negedge nR)
begin
	if(~nR)
	begin
		clkCipherGo <= 1'b0;
		clkKeyGo <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			clkCipherGo <= newData;
			clkKeyGo <= newKey;
		end
		LOAD:
		begin
			ENCDEC <= enc_dec;
			if(enc_dec)	clkCipherGo <= (newData) && (newKey || doneKey);
			else		clkCipherGo <= (newData) && doneKey;
			clkKeyGo <= newKey;
		end
		EXECUTE:
		begin
		end
		WRITE:
		begin
		end
		endcase
	end
end

//	MAIN STATE CONTROL
always_ff @(posedge clkAll, negedge nR)
begin
	if(~nR)
	begin
		current <= INIT;
		count <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			count <= 1'b0;
		end
		LOAD:
		begin
			count <= 1'b0;
		end
		EXECUTE:
		begin
			count <= count + 1'b1;
		end
		WRITE:
		begin
			count <= count;
		end
		endcase
		current <= next;
	end
end

//	CIPHER STATE
always_ff @(posedge clkCipher, negedge nR)
begin
	if(~nR)
	begin
		cipher <= 'b0;
		p <= 'b0;
	end
	else
	begin
		if(readData)	doneData <= 1'b0;
		unique case(current)
		INIT:
		begin
			doneData <= 1'b0;
			ldData <= 1'b0;
		end
		LOAD:
		begin
			if(ENCDEC)		p <= plain;
			else			p <= {plain[N-1:0], plain[2*N-1:N]};
			ldData <= newData;
		end
		EXECUTE:
		begin
			p <= c;
		end
		WRITE:
		begin		
			ldData <= 1'b0;
			if(next == LOAD)
			begin
				doneData <= 1'b1;
				cipher <= ENCDEC ? c : {c[N-1:0], c[2*N-1:N]};
			end
		end
		endcase
	end
end

//	KEY STATE
always_ff @(posedge clkKey, negedge nR)
begin
	if(~nR)
	begin
		keys <= 'b0;
		pKeys <= 'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			doneKey <= 1'b0;
			ldKey <= 1'b0;
		end
		LOAD:
		begin
			for(int i=0; i<M; i++)
			begin
				pKeys[i] <= key[i];
				keys[i] <= key[i];
			end
			ldKey <= newKey;
		end
		EXECUTE:
		begin
			keys[count+M] <= oKey;
			pKeys <= {oKey, pKeys[M-1:1]};
		end
		WRITE:
		begin
			ldKey <= 1'b0;
			doneKey <= 1'b1;
		end
		endcase
	end
end

always_comb
begin
	unique case(current)
	INIT:				next = LOAD;
	LOAD:				next = EXECUTE;
	EXECUTE:
	begin
		if(count >= logic'(T-2))	next = WRITE;
		else			next = EXECUTE;
	end
	WRITE:
	begin
		if(~doneData && ~readData)		next = LOAD;
		else			next = WRITE;
	end
	endcase
end

endmodule
