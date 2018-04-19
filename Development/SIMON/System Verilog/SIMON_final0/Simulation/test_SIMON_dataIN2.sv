module test_SIMON_dataIN2;
parameter N = 16;
parameter M = 4;
parameter T = 32;	
parameter Cb = 5;
parameter MODE = 0;			

logic clk, nR;
logic newPkt;
logic loadData, loadKey;
logic doneData, doneKey;
logic [(1+(N/2)):0][7:0] in;
logic loadPkt, donePkt;
logic newKey, newData;
logic [7:0] infoIN, countIN;
logic [1:0][N-1:0] blockIN;
logic [M-1:0][N-1:0] KEY;

SIMON_dataIN2 dIN(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

logic done;

initial
begin
	repeat(2)	@(posedge clk);

	nR = 1'b0;
	done = 1'b0;
	newPkt = 1'b0;
	loadData = 1'b0;
	loadKey = 1'b0;
	doneData = 1'b0;
	doneKey = 1'b0;

	in = 80'hA0001918111009080100;

	#10ns

	nR = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	newPkt = 1'b1;
end

always @(posedge loadPkt)
begin
	@(posedge clk);
	#10ns

	newPkt <= 1'b0;

	in <= 80'h80016565687721403F21;
end

always @(posedge newData)
begin
	repeat(2)	@(posedge clk);
	#10ns

	loadData <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	loadData <= 1'b0;
end

always @(posedge newKey)
begin
	repeat(2)	@(posedge clk);
	#10ns

	loadKey <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	loadKey <= 1'b0;
end

always @(posedge donePkt)
begin
	@(posedge clk);
	#10ns
	
	if(~done)
	begin
		newPkt <= 1'b1;
		done <= 1'b1;
	end
end

endmodule