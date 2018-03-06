module test_SIMON_96144;
parameter N = 48;
parameter M = 3;
parameter T = 54;
parameter Co = 6;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_96144 #(N,M,T,Co) c(.*);

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

	inputStream[0] = 96'h74616874207473756420666F;
	inputStream[1] = 96'hA8D5F7DE0123FEDC01234567;
	inputStream[2] = 96'h5BC92D014567BA9889ABCDEF;
	inputStream[3] = 96'hF2B48D4589AB765401234567;
	inputStream[4] = 96'h567F11DECDEF321089ABCDEF;

	plain = inputStream[0];
	//key[3] = 48'h1A1918;
	key[2] = 48'h151413121110;
	key[1] = 48'h0D0C0B0A0908;
	key[0] = 48'h050403020100;

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
