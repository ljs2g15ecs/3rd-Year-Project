module SIMON_3264
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0					)
 (	input logic 			clk, nR,
	input logic 			newData, newKey,
	input logic 			enc_dec, readData,
	input logic [1:0][N-1:0]	blockIN,
	input logic [M-1:0][N-1:0] 	KEY,
	output logic 			loadData, loadKey,
	output logic 			doneData, doneKey,
	output logic [1:0][N-1:0] 	outData			);

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0]			pKeys;
logic [N-1:0]				oKey, rKey;
logic [Cb-1:0]				count;
const reg [61:0] z = 62'b01100111000011010100100010111110110011100001101010010001011111;
SIMON_keyexpansion #(N,M,Cb) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

//	CIPHER LOGIC
logic [1:0][N-1:0]			i, o;
SIMON_round #(N) r(.in(i), .key(rKey), .out(o));

//	CONTROL LOGIC
logic [7:0] infoIN, infoOUT, countIN, countOUT;
SIMON_control #(N,M,T,Cb) control(.*);

endmodule
