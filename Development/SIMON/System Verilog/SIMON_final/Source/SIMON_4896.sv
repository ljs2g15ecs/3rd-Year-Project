module SIMON_4896
#(	parameter N = 24,
	parameter M = 4,
	parameter T = 36,		
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

reg [61:0] z = 62'b01011010000110010011111011100010101101000011001001111101110001;

SIMON_keyexpansion #(N,M,Co) ke(.count(count), .keys(pKeys), .z(z), .out(oKey));

SIMON_control #(N,M,T,Co) control(.*);

endmodule
