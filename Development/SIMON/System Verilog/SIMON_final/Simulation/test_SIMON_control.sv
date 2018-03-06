module test_SIMON_control_v5;
parameter N = 16;
parameter M = 4;
parameter T = 32;
parameter C = 5;

logic clk, nR;
logic newData, newKey;
logic enc_dec, readData;
logic [2*N-1:0] plain;
logic [M-1:0][N-1:0] key;
logic ldData, ldKey;
logic doneData, doneKey;
logic [2*N-1:0] cipher;

SIMON_control_v5 c(.*);

int cipherCount;

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
	cipherCount = 0;

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

	/*
	#12000ns
	nR = 1'b0;

	#1000ns
	nR = 1'b1;

	#250ns
	newData = 1'b1;
	newKey = 1'b1;
	//*/
	if(cipherCount > 4) $finish;
end

always @(posedge doneData)
begin
	#110ns
	newData = 1'b1;
	if(cipherCount == 0)
	begin
		#4000ns
		readData = 1'b1;
		outputStream[cipherCount] = cipher;
	end
	else
	begin
		#100ns
		readData = 1'b1;
		outputStream[cipherCount] = cipher;
	end
	cipherCount++;
end

always @(negedge doneData)
begin
	repeat(2)	@(posedge clk);
	#20ns
	readData = 1'b0;
end

always @(posedge ldData)
begin
	repeat(2)	@(posedge clk);
	#20ns
	newData = 1'b0;
	plain = inputStream[cipherCount+1];
end

always @(posedge ldKey)
begin
	repeat(2)	@(posedge clk);
	#20ns
	newKey = 1'b0;
end

endmodule
