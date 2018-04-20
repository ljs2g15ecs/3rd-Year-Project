//	SIMON_definitions.vh

`ifndef _SIMON_DEF_SVH_
`define _SIMON_DEF_SVH_

`define 	MODE0
`define		PKT

`ifdef 		MODE0
	`define	MODE	0
	`define	N	16
	`define	M	4
	`define	M4
	`define	T	32
	`define	J0
	`define	Cb	5
		
	`define	inTEST 	32'h65656877;
	`define	KEY_TEST	64'h1918111009080100;
`else `ifdef MODE1
	`define	MODE	1
	`define	N	24
	`define	M	3
	`define	T	36
	`define	J0
	`define	Cb	6
`else `ifdef MODE2
	`define	MODE	2
	`define	N	24
	`define	M	4
	`define	M4
	`define	T	36
	`define	J1
	`define	Cb	6
`else `ifdef MODE3
	`define	MODE	3
	`define	N	32
	`define	M	3
	`define	T	42
	`define	J2
	`define	Cb	6
`else `ifdef MODE4
	`define	MODE	4
	`define	N	32
	`define	M	4
	`define	M4
	`define	T	44
	`define	J3
	`define	Cb	6
`else `ifdef MODE5
	`define	MODE	5
	`define	N	48
	`define	M	2
	`define	T	52
	`define	J2
	`define	Cb	6
`else `ifdef MODE6
	`define	MODE	6
	`define	N	48
	`define	M	3
	`define	T	54
	`define	J3
	`define	Cb	6
`else `ifdef MODE7
	`define	MODE	7
	`define	N	64
	`define	M	2
	`define	T	68
	`define	J2
	`define	Cb	7
`else `ifdef MODE8
	`define	MODE	8
	`define	N	64
	`define	M	3
	`define	T	69
	`define	J3
	`define	Cb	7
`else `ifdef MODE9
	`define	MODE	9
	`define	N	64
	`define	M	4
	`define	M4
	`define	T	72
	`define	J4
	`define	Cb	7
`endif
`endif
`endif
`endif
`endif
`endif
`endif
`endif
`endif
`endif

`endif