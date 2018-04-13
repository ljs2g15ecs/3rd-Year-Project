module test_SIMON_dataOUT;

parameter N = 16;
parameter M = 4;
parameter T = 32;	
parameter Cb = 5;
parameter MODE = 0;

logic clk, nR;
logic readOUT;
logic doneData;
logic [7:0] infoOUT, countOUT;
logic [1:0][N-1:0] blockOUT;
logic [M-1:0][N-1:0] KEY;
logic newOUT, doneOUT;
logic readData;
logic [(1+(N/2)):0][7:0] out;

SIMON_dataOUT #(N,M,T,Cb,MODE) dOUT(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	@(posedge clk);

	nR = 1'b0;
	readOUT = 1'b0;
	doneData = 1'b0;
	
	infoOUT = 8'hD0;
	countOUT = 'b0;
	blockOUT = 'b0;
	KEY = 'b0;

	#10ns

	nR = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	doneData = 1'b1;
end

always @(posedge readData)
begin
	repeat(2)	@(posedge clk);
	#10ns

	doneData <= 1'b0;

	repeat(5)	@(posedge clk);
	#10ns

	doneData <= 1'b1;
end

endmodule
