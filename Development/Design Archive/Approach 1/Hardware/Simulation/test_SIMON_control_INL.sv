module test_SIMON_control_INL;

parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter C = 5;

logic clk, nR;
logic newData, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;

logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_control_INL c(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

`define	KEY	64'h1918111009080100
`define PLAIN	32'h65656877
`define CIPHER	32'hC69BE9BB

initial
begin
	nR = 1'b0;

	@(posedge clk)
	#10ns

	newData = 1'b0;
	readData = 1'b0;
	plain = `PLAIN;
	key = `KEY;

	@(posedge clk)
	#10ns

	nR = 1'b1;

	@(posedge clk)
	#10ns

	newData = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	newData = 1'b0;

	@(posedge doneData);
	
	repeat(2)	@(posedge clk);
	#10ns

	readData = 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	readData = 1'b0;

	$finish;
end

endmodule
