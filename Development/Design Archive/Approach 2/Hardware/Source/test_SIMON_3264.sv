module test_SIMON_3264;
parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter Co = 5;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_3264 #(N,M,T,Co) c(.*);

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
	newKey = 1'b0;
	readData = 1'b0;
	enc_dec = 1'b1;

	plain = `PLAIN;
	key = `KEY;

	@(posedge clk)
	#10ns

	nR = 1'b1;
	
	@(posedge clk)
	#10ns

	newData = 1'b1;
	newKey = 1'b1;
end

always @(posedge ldData)
begin
	repeat(2)	@(posedge clk);
	#20ns
	newData <= 1'b0;
end

always @(posedge doneData)
begin
	repeat(2)	@(posedge clk);
	#10ns
	readData <= 1'b1;
	plain <= cipher;
	enc_dec <= ~enc_dec;
	
	repeat(2)	@(posedge clk);
	#10ns
	newData <= 1'b1;
end

always @(negedge doneData)
begin
	repeat(2)	@(posedge clk);
	#20ns
	readData = 1'b0;
end

always @(posedge ldKey)
begin
	repeat(2)	@(posedge clk);
	#20ns
	newKey <= 1'b0;
end

endmodule