module test_SIMON_9696;
parameter N = 48;
parameter M = 2;
parameter T = 52;
parameter Co = 6;

logic 			clk, nR;
logic 			newData, newKey;
logic 			enc_dec, readData;
logic [1:0][N-1:0]	BLOCK;
logic [M-1:0][N-1:0] 	KEY;
logic 			loadData, loadKey;
logic 			doneData, doneKey;
logic [1:0][N-1:0] 	outData;
logic [3:0]		mode;		

SIMON_9696 #(N,M,T,Co) c(.*);

int inputCount, outputCount;

logic [1:0][4:0][2*N-1:0] inputStream, outputStream;

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

	inputStream[enc_dec][0] = 96'h2072616C6C69702065687420;
	inputStream[enc_dec][1] = 96'hA8D5F7DE0123FEDC01234567;
	inputStream[enc_dec][2] = 96'h5BC92D014567BA9889ABCDEF;
	inputStream[enc_dec][3] = 96'hF2B48D4589AB765401234567;
	inputStream[enc_dec][4] = 96'h567F11DECDEF321089ABCDEF;

	BLOCK = inputStream[enc_dec][0];
	//KEY[3] = 48'h1A1918;
	//KEY[2] = 48'h13121110;
	KEY[1] = 48'h0D0C0B0A0908;
	KEY[0] = 48'h050403020100;

	#250ns
	newData = 1'b1;
	newKey = 1'b1;
end

always @(posedge newData)
begin
	$display("Plaintext Available:	%h @ %tns", inputStream[enc_dec][inputCount], $time);
	@(posedge loadData)
	$display("Plaintext Loaded:	%h @ %tns", inputStream[enc_dec][inputCount], $time);
	inputCount++;
	repeat(2)	@(posedge clk);
	#20ns
	newData = 1'b0;
	BLOCK = inputStream[enc_dec][inputCount];
end

always @(posedge doneData)
begin
	$display("Plaintext Encrypted:	%h @ %tns", inputStream[enc_dec][inputCount-1], $time);
	repeat(1)	@(posedge clk);
	#20ns
	if(inputCount < 5)	newData = 1'b1;
	repeat(2)	@(posedge clk);
	#20ns
	readData = 1'b1;
	outputStream[enc_dec][outputCount] = outData;
	$display("Ciphertext Read:	%h @ %tns", outputStream[enc_dec][outputCount], $time);
	outputCount++;
	if(outputCount >= 5)	#500ns	nR = 1'b0;
end

always @(negedge nR)
begin
	if(enc_dec)
	begin	
		repeat(10)	@(posedge clk);
		#10ns
		enc_dec = ~enc_dec;
		inputStream[enc_dec] = outputStream[~enc_dec];
		inputCount = 0;
		outputCount = 0;
		BLOCK = inputStream[enc_dec][0];
		nR = 1'b1;
		#250ns
		newData = 1'b1;
		newKey = 1'b1;
	end
	else
	begin
		for(int i=0; i<5; i++)
		begin
			if(inputStream[1][i] == outputStream[0][i])
			begin
				$display("Plaintext: %h SUCCESS!!", inputStream[1][i]);
			end
		end
		repeat(10)	@(posedge clk);
		#10ns
		$finish;
	end
end

always @(negedge doneData)
begin
	repeat(2)	@(posedge clk);
	#20ns
	readData = 1'b0;
end

always @(posedge loadKey)
begin
	repeat(2)	@(posedge clk);
	#20ns
	newKey = 1'b0;
end

final 
$display(" END OF SIMULATION at %d ",$time); 
endmodule
