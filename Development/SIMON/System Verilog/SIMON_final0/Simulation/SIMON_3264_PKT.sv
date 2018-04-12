module SIMON_3264_PKT
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0			)
 (	input logic clk, nR,
	input logic newIN,
	input logic [(1+(N/2)):0][7:0] in,
	output logic loadPkt, donePkt,
	output logic [1:0][N-1:0] outData	);

logic newData, newKey;
logic loadData, loadKey;
logic doneData, doneKey;
logic readData;
logic enc_dec;

logic [7:0] info, infoCOUNT;

logic [1:0][N-1:0] BLOCK;
logic [M-1:0][N-1:0] KEY;

SIMON_dataIN #(N,M,T,Cb,MODE) dIN(.*);

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
SIMON_control #(N,M,T,Cb) control(.*);

endmodule
