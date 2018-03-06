module SIMON_128256
#(	parameter N = 64,
	parameter M = 4,
	parameter T = 72,		
	parameter Cb = 7					)
 (	input logic 			clk, nR,
	input logic 			newData, newKey,
	input logic 			enc_dec, readData,
	input logic [1:0][N-1:0]	inData,
	input logic [M-1:0][N-1:0] 	key,
	output logic 			loadData, loadKey,
	output logic 			doneData, doneKey,
	output logic [1:0][N-1:0] 	outData);

`define M4

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0]			pKeys;
logic [N-1:0]				oKey, rKey;
logic [Cb-1:0]				count;
reg [61:0] z = 62'b11110111001001010011000011101000000100011011010110011110001011;
SIMON_keyexpansion #(N,M,Cb) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

//	CIPHER LOGIC
logic [1:0][N-1:0]			i, o;
SIMON_round #(N) r(.in(i), .key(rKey), .out(o));

//	CONTROL LOGIC
SIMON_control #(N,M,T,Cb) control(.*);


endmodule
