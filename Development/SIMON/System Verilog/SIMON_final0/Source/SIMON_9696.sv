module SIMON_9696
#(	parameter N = 48,
	parameter M = 2,
	parameter T = 52,		
	parameter Cb = 6					)
 (	input logic 			clk, nR,
	input logic 			newData, newKey,
	input logic 			enc_dec, readData,
	input logic [1:0][N-1:0]	inData,
	input logic [M-1:0][N-1:0] 	key,
	output logic 			loadData, loadKey,
	output logic 			doneData, doneKey,
	output logic [1:0][N-1:0] 	outData,
	output logic [3:0]		mode			);

//`define M4

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0]			pKeys;
logic [N-1:0]				oKey, rKey;
logic [Cb-1:0]				count;
reg [61:0] z = 62'b11001101101001111110001000010100011001001011000000111011110101;
SIMON_keyexpansion #(N,M,Cb) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

//	CIPHER LOGIC
logic [1:0][N-1:0]			i, o;
SIMON_round #(N) r(.in(i), .key(rKey), .out(o));

//	CONTROL LOGIC
SIMON_control #(N,M,T,Cb) control(.*);

endmodule
