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

int inputCount, outputCount;

logic [4:0][2*N-1:0] inputStream, outputStream;

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	#10ns
	nR = 1'b1;
	newData = 1'b0;
	newKey = 1'b0;
	readData = 1'b0;
	enc_dec = 1'b1;
	inputCount = 0;
	outputCount = 0;

	inputStream[0] = 32'h65656877;
	inputStream[1] = 32'hA8D5F7DE;
	inputStream[2] = 32'h5BC92D01;
	inputStream[3] = 32'hF2B48D45;
	inputStream[4] = 32'h567F11DE;

	plain = inputStream[0];
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;

	#250ns
	newData = 1'b1;
	newKey = 1'b1;
end

always @(posedge newData)
begin
	@(posedge ldData);
	inputCount++;
	repeat(2)	@(posedge clk);
	#20ns
	newData = 1'b0;
	plain = inputStream[inputCount];
end

always @(posedge doneData)
begin
	repeat(1)	@(posedge clk);
	#20ns
	if(inputCount < 5)	newData = 1'b1;
	repeat(2)	@(posedge clk);
	#20ns
	readData = 1'b1;
	outputStream[outputCount] = cipher;
	outputCount++;
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
	newKey = 1'b0;
end

endmodule
