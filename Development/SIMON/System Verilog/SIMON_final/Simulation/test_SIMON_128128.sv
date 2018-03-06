module test_SIMON_128128;
parameter N = 64;
parameter M = 2;
parameter T = 68;
parameter Co = 7;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_128128 #(N,M,T,Co) c(.*);

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

	inputStream[0] = 128'h63736564207372656C6C657661727420;
	inputStream[1] = 128'hA8D5F7DE0123FEDC01234567FEDCBA98;
	inputStream[2] = 128'h5BC92D014567BA9889ABCDEF01234567;
	inputStream[3] = 128'hF2B48D4589AB765401234567FEDCBA98;
	inputStream[4] = 128'h567F11DECDEF321089ABCDEF01234567;

	plain = inputStream[0];
	//key[3] = 64'h1A1918;
	//key[2] = 64'h151413121110;
	key[1] = 64'h0F0E0D0C0B0A0908;
	key[0] = 64'h0706050403020100;

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
