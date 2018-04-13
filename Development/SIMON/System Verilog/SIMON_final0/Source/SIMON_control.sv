module SIMON_control
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,
	parameter Cb = 5					)
 (	input logic 			clk, nR,
	input logic 			newData, newKey,
	input logic 			enc_dec, readData,
	input logic [1:0][N-1:0] 	blockIN, o,
	input logic [M-1:0][N-1:0] 	KEY,
	input logic [N-1:0] 		oKey,
	input logic [7:0]		infoIN, countIN,
	output logic 			loadData, loadKey,
	output logic 			doneData, doneKey,
	output logic [1:0][N-1:0] 	outData, i,
	output logic [M-1:0][N-1:0] 	pKeys,
	output logic [N-1:0]		rKey,
	output logic [Cb-1:0] 		count,
	output logic [7:0]		infoOUT, countOUT	);

//	STATES
typedef enum bit [1:0] {INIT, LOAD, EXECUTE, WRITE} state;
state current, next;

//	KEY EXPANSION LOGIC
logic [T-1:0][N-1:0] keys;
logic ENCDEC;
assign rKey = ENCDEC ? keys[count] : keys[T-(count+1)];

//	GATED CLOCK LOGIC
logic clkCipherGo, clkCipher;
logic clkKeyGo, clkKey, clkAll;

assign clkCipher = clk && clkCipherGo;
assign clkKey = clk && clkKeyGo;
assign clkAll = clkCipher || clkKey;

//	CLOCK CONTROL
//	At negedge to avoid glitches
always_ff @(negedge clk, negedge nR)
begin
	if(~nR)
	begin
		clkCipherGo <= 1'b0;
		clkKeyGo <= 1'b0;
		ENCDEC <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			clkCipherGo <= 1'b1;
			clkKeyGo <= 1'b1;
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
		
		infoOUT <= 'b0;
		countOUT <= 'b0;
		
		doneData <= 1'b0;
	end
	else
	begin
		if(readData)	doneData <= 1'b0;
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
			if(next == LOAD)
			begin
				doneData <= 1'b1;
				infoOUT <= {infoIN[7:5], ~infoIN[4], infoIN[3:0]};
				countOUT <= countIN;
			end
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
		outData <= 'b0;
		i <= 'b0;
		loadData <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			doneData <= 1'b0;
			loadData <= 1'b0;
		end
		LOAD:
		begin		
			if(ENCDEC)		i <= blockIN;
			else			i <= {blockIN[0], blockIN[1]};
			loadData <= 1'b1;
		end
		EXECUTE:
		begin		
			i <= o;
		end
		WRITE:
		begin		
			loadData <= 1'b0;
			if(next == LOAD)
			begin
				outData <= ENCDEC ? o : {o[0], o[1]};
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
		loadKey <= 1'b0;
		doneKey <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			loadKey <= 1'b0;
			doneKey <= 1'b0;
		end
		LOAD:
		begin
			for(int i=0; i<M; i++)
			begin
				pKeys[i] <= KEY[i];
				keys[i] <= KEY[i];
			end
			loadKey <= 1'b1;
		end
		EXECUTE:
		begin
			keys[count+M] <= oKey;
			pKeys <= {oKey, pKeys[M-1:1]};
		end
		WRITE:
		begin
			loadKey <= 1'b0;
			doneKey <= 1'b1;
		end
		endcase
	end
end

//	NEXT STATE LOGIC
always_comb
begin
	unique case(current)
	INIT:				next = LOAD;
	LOAD:				next = EXECUTE;
	EXECUTE:
	begin
		if(count == T-2)	next = WRITE;
		else			next = EXECUTE;
	end
	WRITE:
	begin
		if(doneData || readData)next = WRITE;
		else			next = LOAD;
	end
	endcase
end

endmodule