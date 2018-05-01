`include "SIMON_defintions.svh"

module SIMON_topPKT
(
input logic				clk, nR,
input logic				in_newPKT,
input logic				out_readPKT,
input logic [(1+(`N/2)):0][7:0]		in,
output logic 				in_loadPKT, in_donePKT,
output logic				out_donePKT,
output logic [(1+(`N/2)):0][7:0]	out
);

//	DATA FLOW CONTROL LOGIC
logic					newDATA, newKEY;
logic					newDATA_rise, newKEY_rise;
logic					loadDATA, loadKEY;
logic					doneDATA, doneKEY;
logic					readDATA;

//	PACKET INFO LOGIC
logic [7:0]				infoIN, countIN;
logic [7:0]				infoOUT, countOUT;

//	DATA LOGIC
logic [1:0][`N-1:0]			inDATA;
logic [`M-1:0][`N-1:0]			KEY;
logic [1:0][`N-1:0]			outDATA;

SIMON_dataIN				dataIN(.*);
SIMON_control				control(.*);
SIMON_dataOUT				dataOUT(.*);

endmodule