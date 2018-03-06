module SIMON_64128
#(	parameter N = 32,
	parameter M = 4,
	parameter T = 44,		
	parameter Co = 6		)
 (	input logic clk, nR,
	input logic newData, newKey,
	input logic enc_dec, readData,
	input logic [2*N-1:0] plain,
	input logic [M-1:0][N-1:0] key,
	output logic ldData, ldKey,
	output logic doneData, doneKey,
	output logic [2*N-1:0] cipher	);

//	KEY EXPANSION LOGIC
logic [M-1:0][N-1:0] pKeys;
logic [N-1:0] oKey;
logic [Co-1:0] count;

reg [61:0] z = 62'b11110000101100111001010001001000000111101001100011010111011011;

SIMON_keyexpansion #(N,M,Co) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

SIMON_control #(N,M,T,Co) control(.*);

endmodule
