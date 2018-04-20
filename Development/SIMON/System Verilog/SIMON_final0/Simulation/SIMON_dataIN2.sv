module SIMON_dataIN2
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0			)
 (	input logic clk, nR,
	input logic newPkt,
	input logic loadData, loadKey,
	input logic [(1+(N/2)):0][7:0] in,
	output logic loadPkt, donePkt,
	output logic newKey, newData,
	output logic [7:0] infoIN, countIN,
	output logic [1:0][N-1:0] blockIN,
	output logic [M-1:0][N-1:0] KEY		);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, COMPUTE, WRITE} state;
state current, next;

logic				newPkt_rise;

logic [(1+(N/2)):0][7:0] 	pkt;
logic				nBLOCK, PROCESSING;
logic [7:0] 			info, countPkt;
logic [3:0][N-1:0] 		data;

assign data[0] = pkt[(N/8)-1:0];
assign data[1] = pkt[(N/4)-1:(N/8)];
assign data[2] = pkt[(3*N/8)-1:(N/4)];
assign data[3] = pkt[(N/2)-1:(3*N/8)];

assign countIN = pkt[(N/2)];
assign info = pkt[(N/2)+1];

always @(posedge newPkt, posedge loadPkt, negedge nR)
begin
	if(~nR)			newPkt_rise <= 1'b0;
	else if(loadPkt)	newPkt_rise <= 1'b0;
	else if(newPkt)		newPkt_rise <= 1'b1;
end

always @(PROCESSING, negedge nR)
begin
	if(~nR)			donePkt <= 1'b0;
	else if(PROCESSING)	donePkt <= 1'b0;
	else			donePkt <= 1'b1;
end

always @(posedge clk, negedge nR)
begin
	if(~nR)
	begin
		pkt <= 'b0;
		nBLOCK <= 1'b0;
		PROCESSING <= 1'b0;
		infoIN <= 1'b0;
		countPkt <= 'b0;

		loadPkt <= 1'b0;
		newData <= 1'b0;
		newKey <= 1'b0;
		blockIN <= 'b0;
		KEY <= 'b0;
	
		current <= WAIT;
	end
	else
	begin
		if(newData && loadData)	newData <= 1'b0;
		if(newKey && loadKey)	newKey <= 1'b0;
		unique case(current)
		WAIT:
		begin
			loadPkt <= 1'b0;
		end
		LOAD:
		begin
			pkt <= in;
			loadPkt <= 1'b1;
			PROCESSING <= 1'b1;
		end
		COMPUTE:
		begin
			if(countIN != countPkt)		$display("ERROR - PACKET COUNT TRACKER");
			else if(infoIN[3:0] != MODE)	$display("ERROR - INCORRECT MODE");
			else if(infoIN[4])		$display("ERROR - OUTPUT PACKET");
			else
			begin
				countPkt <= countPkt + 1;
				nBLOCK <= ~info[5] && info[7];
			end
		end
		WRITE:
		begin
			if(info[5] && ~loadKey)
			begin
				newKey <= 1'b1;
				for(int i=0; i<M; i++)	KEY[i] <= data[i];
			end
			else if(~info[5] && ~loadData)
			begin
				newData <= 1'b1;
				blockIN[0] <= data[{~nBLOCK, 1'b0}];
				blockIN[1] <= data[{~nBLOCK, 1'b1}];
				nBLOCK <= 1'b0;
			end

			infoIN <= info;

			if(~nBLOCK)	PROCESSING <= 1'b0;
		end
		endcase
		current <= next;
	end
end

always_comb
begin
	unique case(current)
	WAIT:
	begin
		if(PROCESSING)
		begin
			if(newData || loadData)		next = WAIT;	
			else				next = WRITE;	
		end
		else
		begin
			if(newPkt_rise)			next = LOAD;
			else				next = WAIT;
		end
	end
	LOAD:						next = COMPUTE;
	COMPUTE:					next = WRITE;
	WRITE:						next = WAIT;
	endcase
end

endmodule
