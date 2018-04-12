module SIMON_dataOUT
#(	parameter N = 16,
	parameter M = 4,
	parameter T = 32,		
	parameter Cb = 5,
	parameter MODE = 0			)
 (	input logic clk, nR,
	input logic readOUT,
	input logic doneData, doneKey,
	input logic [7:0] info, infoCOUNT,
	input logic [1:0][N-1:0] BLOCK,
	input logic [M-1:0][N-1:0] KEY,
	output logic newOUT, doneOUT,
	output logic readData,
	output logic [(1+(N/2)):0][7:0] out	);

//	STATES
typedef enum bit [1:0] {WAIT, LOAD, COMPUTE, WRITE} state;
state current, next;

logic nBLOCK;

endmodule
