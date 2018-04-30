module SIMON_128128
#(	parameter N = 64,
	parameter M = 2,
	parameter T = 68,		
	parameter Co = 7		)
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

reg [61:0] z = 62'b11001101101001111110001000010100011001001011000000111011110101;

SIMON_keyexpansion #(N,M,Co) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

SIMON_control #(N,M,T,Co) control(.*);

endmodule
