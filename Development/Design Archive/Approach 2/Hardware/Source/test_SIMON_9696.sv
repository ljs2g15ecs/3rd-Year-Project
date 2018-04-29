module test_SIMON_9696;
parameter N = 48;
parameter M = 2;
parameter T = 52;
parameter Co = 6;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_9696 #(N,M,T,Co) c(.*);

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

`define	KEY	96'h0D0C0B0A0908050403020100
`define PLAIN	96'h2072616C6C69702065687420
`define CIPHER	96'h602807A462b469063D8FF082

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
