module SIMON_64128
#(	parameter N = 32,
	parameter M = 4,
	parameter T = 44,		
	parameter Cb = 6					)
 (	input logic 			clk, nR,
	input logic 			newData, newKey,
	input logic 			enc_dec, readData,
	input logic [1:0][N-1:0]	BLOCK,
	input logic [M-1:0][N-1:0] 	KEY,
	output logic 			loadData, loadKey,
	output logic 			doneData, doneKey,
	output logic [1:0][N-1:0] 	outData,
	output logic [3:0]		mode			);

`define M4

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0]			pKeys;
logic [N-1:0]				oKey, rKey;
logic [Cb-1:0]				count;
reg [61:0] z = 62'b11110000101100111001010001001000000111101001100011010111011011;
SIMON_keyexpansion #(N,M,Cb) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

//	CIPHER LOGIC
logic [1:0][N-1:0]			i, o;
SIMON_round #(N) r(.in(i), .key(rKey), .out(o));

//	CONTROL LOGIC
SIMON_control #(N,M,T,Cb) control(.*);

endmodule
