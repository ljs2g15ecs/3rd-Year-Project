`include "SIMON_defintions.svh"

module SIMON_control
(	input logic 			clk, nR,
	input logic 			newDATA, newKEY,
	input logic 			readDATA,
	input logic [7:0]		infoIN, countIN,
	input logic [1:0][`N-1:0]	inDATA,
	input logic [`M-1:0][`N-1:0]	KEY,
	output logic			newDATA_rise, newKEY_rise,
	output logic			loadDATA, loadKEY,
	output logic			doneDATA, doneKEY,
	output logic [7:0]		infoOUT, countOUT,
	output logic [1:0][`N-1:0]	outDATA			);

//	STATES
typedef enum bit [1:0] {INIT, LOAD, EXECUTE, WRITE} state;
state current, next;

logic [7:0]				info, countPKT;

//	KEY EXPANSION LOGIC
logic					ENC_DEC;
logic [`Cb-1:0]				count;
logic [`M-1:0][`N-1:0] 			pKeys;
logic [`T-1:0][`N-1:0] 			keys;
logic [`N-1:0] 				oKey, rKey;

SIMON_keyexpansion ke(.count(count), .keys(pKeys), .out(oKey));
assign rKey = ENC_DEC ? keys[count] : keys[`T-(count+1)];

//	CIPHER LOGIC
logic [2*`N-1:0] 			i, o;

SIMON_round r(.in(i), .key(rKey), .out(o));

//	RISING EDGE NEW CHECK
always @(posedge newDATA, posedge loadDATA, negedge nR)
begin
	if(~nR)				newDATA_rise <= 1'b0;
	else if(loadDATA)		newDATA_rise <= 1'b0;
	else if(newDATA)		newDATA_rise <= 1'b1;
end

always @(posedge newKEY, posedge loadKEY, negedge nR)
begin
	if(~nR)				newKEY_rise <= 1'b0;
	else if(loadKEY)		newKEY_rise <= 1'b0;
	else if(newKEY)			newKEY_rise <= 1'b1;
end

//	GATED CLOCK LOGIC
logic clkDATAGo, clkDATA;
logic clkKEYGo, clkKEY, clkALL;

assign clkDATA = clk && clkDATAGo;
assign clkKEY = clk && clkKEYGo;
assign clkALL = clkDATA || clkKEY;

always_ff @(negedge clk, negedge nR)
begin
	if(~nR)
	begin
		clkDATAGo <= 1'b0;
		clkKEYGo <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			clkDATAGo <= 1'b1;
			clkKEYGo <= 1'b1;
		end
		LOAD:
		begin
			if(infoIN[6])	clkDATAGo <= (newDATA_rise) && (newKEY_rise || doneKEY);
			else		clkDATAGo <= (newDATA_rise) && doneKEY;
			clkKEYGo <= newKEY;
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

always_ff @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		doneDATA <= 1'b0;
	end
	else
	begin
		if(doneDATA && readDATA)	doneDATA <= 1'b0;		
		unique case(current)
		INIT:
		begin
			
		end
		LOAD:
		begin
			
		end
		EXECUTE:
		begin
			
		end
		WRITE:
		begin
			if(next == LOAD)
			begin				
				doneDATA <= 1'b1;
			end
		end
		endcase
	end
end

//	MAIN STATE CONTROL
always_ff @(posedge clkALL, negedge nR)
begin
	if(~nR)
	begin
		ENC_DEC <= 1'b0;
		count <= 1'b0;
		info <= 'b0;
		infoOUT <= 'b0;
		countPKT <= 'b0;
		countOUT <= 'b0;
	end
	else
	begin	
		unique case(current)
		INIT:
		begin
			
		end
		LOAD:
		begin
			count <= 1'b0;
			info <= infoIN;
			ENC_DEC <= infoIN[6];
			countPKT <= countIN;
		end
		EXECUTE:
		begin
			count <= count + 1'b1;
		end
		WRITE:
		begin
			if(next == LOAD)
			begin				
				infoOUT <= {info[7:5], ~info[4], info[3:0]};
				countOUT <= countPKT;
			end
		end
		endcase
		current <= next;
	end
end

//	CIPHER STATE
always_ff @(posedge clkDATA, negedge nR)
begin
	if(~nR)
	begin
		outDATA <= 'b0;
		i <= 'b0;
		loadDATA <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			
		end
		LOAD:
		begin		
			if(infoIN[6])		i <= inDATA;
			else			i <= {inDATA[0], inDATA[1]};
			loadDATA <= 1'b1;
		end
		EXECUTE:
		begin		
			loadDATA <= 1'b0;
			i <= o;
		end
		WRITE:
		begin		
			if(next == LOAD)
			begin
				outDATA <= o;
			end
		end
		endcase
	end
end

//	KEY STATE
always_ff @(posedge clkKEY, negedge nR)
begin
	if(~nR)
	begin
		keys <= 'b0;
		pKeys <= 'b0;
		loadKEY <= 1'b0;
		doneKEY <= 1'b0;
	end
	else
	begin
		unique case(current)
		INIT:
		begin
			
		end
		LOAD:
		begin
			for(int i=0; i<`M; i++)
			begin
				pKeys[i] <= KEY[i];
				keys[i] <= KEY[i];
			end
			loadKEY <= 1'b1;
		end
		EXECUTE:
		begin
			keys[count+`M] <= oKey;
			pKeys <= {oKey, pKeys[`M-1:1]};
			loadKEY <= 1'b0;
		end
		WRITE:
		begin
			if(next == LOAD)
			begin
				doneKEY <= 1'b1;
			end
		end
		endcase
	end
end

//	NEXT STATE LOGIC
always_comb
begin
	unique case(current)
	INIT:				next = LOAD;
	LOAD:
	begin
		if(newDATA_rise || newKEY_rise)
					next = EXECUTE;
		else			next = LOAD;
	end
	EXECUTE:
	begin
		if(count == `T-2)	next = WRITE;
		else			next = EXECUTE;
	end
	WRITE:
	begin
		if(clkKEYGo && ~clkDATAGo)
					next = LOAD;
		else if(doneDATA || readDATA)
					next = WRITE;
		else			next = LOAD;
	end
	endcase
end

endmodule
