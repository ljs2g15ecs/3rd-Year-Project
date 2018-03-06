module SIMON_control_v2
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

/*
logic [M-1:0][N-1:0] pKeys;
logic [T-1:0][N-1:0] keys;
logic [N-1:0] oKey, rKey;
SIMON_keyexpansion ke(.count(count), .keys(pKeys), .out(oKey));
//*/

logic [N-1:0] rKey;
SIMON_keyexpansion_v2 ke(.*);

///*
logic [2*N-1:0] p, c;
SIMON_round r(.block(p), .key(rKey), . out(c) );
//*/


typedef enum {s0, s1, s2} state;
state current, next;

assign cipher = doneData ? p : 'bZ;

logic gateClk;
assign gateClk = ~doneData & clk;

always_ff @(posedge newData)
begin
	ldData <= 1'b1;
end

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
			/*
			p <= plain;
			count <= 0;
			//doneData <= 1'b0;
			foreach(key[i])	pKeys[i] <= key[i];
			if(newKey)	doneKey <= 1'b0;
			else		doneKey <= 1'b1;
			//*/
			
			p <= plain;
			count <= 0;
			if(newData)	ldData <= 1'b0;
		end
		s1:
		begin
			/*
			if(~doneKey)
			begin
				pKeys <= {oKey, pKeys[M-1:1]};
				keys[count] <= pKeys[0];
			end
			
			if(count != T-1)
			begin
				p <= c;
				count <= count + 1;
			end
			else
			begin
				doneKey <= 1'b1;
				//doneData <= 1'b1;
			end
			//*/
			p <= c;
			count <= count + 1;
		end
		s2:
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
		/*
		next = s1;
		doneData = 1'b0;
		//*/
		if(newData)
		begin
			next = s1;
			doneData = 1'b0;
		end
	end
	s1:
	begin
		/*
		if(count == T-1)
		begin
			next = s2;
			doneData = 1'b1;
		end
		//*/
		if(count < T-1)	next = s1;
		else		next = s2;
	end
	s2:
	begin
		/*
		if(newData)	next = s0;
		else		next = s2;
		//*/
		next = s0;
		if(newData)	doneData = 1'b0;
		else		doneData = 1'b1;
	end
	endcase
end

endmodule
