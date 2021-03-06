module test_SIMON_control_v4;
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

SIMON_control_v4 c(.*);

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

	plain = 32'h65656877;
	key[3] = 16'h1918;
	key[2] = 16'h1110;
	key[1] = 16'h0908;
	key[0] = 16'h0100;
	
	#250ns
	newData = ~newData;
	//newKey = ~newKey;
	//readData = ~readData;

	#250ns
	//newData = ~newData;
	newKey = ~newKey;
	//readData = ~readData;

	#250ns
	newData = ~newData;
	newKey = ~newKey;
	readData = ~readData;

	#3750ns
	newData = ~newData;
	//newKey = ~newKey;
	//readData = ~readData;

	#250ns
	newData = ~newData;
	//newKey = ~newKey;
	//readData = ~readData;
end

endmodule
