`include "SIMON_defintions.svh"

module SIMON_top
(
input logic				clk, nR,
input logic				in_newPKT,
input logic				out_readPKT, 
output logic 				in_loadPKT, in_donePKT,
output logic				out_donePKT
);

logic [(1+(`N/2)):0][7:0]		in;
logic [(1+(`N/2)):0][7:0]		out;

SIMON_topPKT topPKT(.*);

endmodule

