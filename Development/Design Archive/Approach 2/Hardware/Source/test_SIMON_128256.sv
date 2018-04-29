module test_SIMON_128256;
parameter N = 64;
parameter M = 4;
parameter T = 72;
parameter Co = 7;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_128256 #(N,M,T,Co) c(.*);

logic encrypt, encryptPASS, decryptPASS, doneSIM;
assign doneSIM = encryptPASS && decryptPASS;

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

`define	KEY	256'h1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100
`define PLAIN	128'h74206E69206D6F6F6D69732061207369
`define CIPHER	128'h8D2B5579AFC8A3A03BF72A87EfE7B868

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
