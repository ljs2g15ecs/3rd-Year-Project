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

	//	TEST VECTORS
	`define	in_KEY_TEST	64'h1918111009080100
	`define	in_ENC_TEST 	32'h65656877
	`define	in_DEC_TEST	32'hC69BE9BB
	`define	in_iKEY_TEST	8'hE0
	`define	in_iENC_TEST	8'hC0
	`define	in_iDEC_TEST	8'h80

	`define	out_ENC_TEST	32'hC69BE9BB
	`define	out_DEC_TEST	32'h65656877
	`define out_iKEY_TEST	8'hF0
	`define	out_iENC_TEST	8'hD0
	`define	out_iDEC_TEST	8'h90
`else `ifdef MODE1
	`define	MODE	1
	`define	N	24
	`define	M	3
	`define	T	36
	`define	J0
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	96'h1211100A0908020100000000
	`define	in_ENC_TEST 	48'h6120676E696C
	`define	in_DEC_TEST	48'hDAE5AC292CAC
	`define	in_iKEY_TEST	8'hE1
	`define	in_iENC_TEST	8'hC1
	`define	in_iDEC_TEST	8'h81

	`define	out_ENC_TEST	48'hDAE5AC292CAC
	`define	out_DEC_TEST	48'h6120676E696C
	`define out_iKEY_TEST	8'hF1
	`define	out_iENC_TEST	8'hD1
	`define	out_iDEC_TEST	8'h91
`else `ifdef MODE2
	`define	MODE	2
	`define	N	24
	`define	M	4
	`define	M4
	`define	T	36
	`define	J1
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	96'h1A19181211100A0908020100
	`define	in_ENC_TEST 	48'h72696320646E
	`define	in_DEC_TEST	48'h6E06A5ACF156
	`define	in_iKEY_TEST	8'hE2
	`define	in_iENC_TEST	8'hC2
	`define	in_iDEC_TEST	8'h82

	`define	out_ENC_TEST	48'h6E06A5ACF156
	`define	out_DEC_TEST	48'h72696320646E
	`define out_iKEY_TEST	8'hF2
	`define	out_iENC_TEST	8'hD2
	`define	out_iDEC_TEST	8'h92
`else `ifdef MODE3
	`define	MODE	3
	`define	N	32
	`define	M	3
	`define	T	42
	`define	J2
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	128'h131211100B0A09080302010000000000
	`define	in_ENC_TEST 	64'h6F7220676E696C63
	`define	in_DEC_TEST	64'h5CA2E27F111A8FC8
	`define	in_iKEY_TEST	8'hE3
	`define	in_iENC_TEST	8'hC3
	`define	in_iDEC_TEST	8'h83

	`define	out_ENC_TEST	64'h5CA2E27F111A8FC8
	`define	out_DEC_TEST	64'h6F7220676E696C63
	`define out_iKEY_TEST	8'hF3
	`define	out_iENC_TEST	8'hD3
	`define	out_iDEC_TEST	8'h93
`else `ifdef MODE4
	`define	MODE	4
	`define	N	32
	`define	M	4
	`define	M4
	`define	T	44
	`define	J3
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	128'h1B1A1918131211100B0A090803020100
	`define	in_ENC_TEST 	64'h656B696C20646E75
	`define	in_DEC_TEST	64'h44C8FC20B9DFA07A
	`define	in_iKEY_TEST	8'hE4
	`define	in_iENC_TEST	8'hC4
	`define	in_iDEC_TEST	8'h84

	`define	out_ENC_TEST	64'h44C8FC20B9DFA07A
	`define	out_DEC_TEST	64'h656B696C20646E75
	`define out_iKEY_TEST	8'hF4
	`define	out_iENC_TEST	8'hD4
	`define	out_iDEC_TEST	8'h94
`else `ifdef MODE5
	`define	MODE	5
	`define	N	48
	`define	M	2
	`define	T	52
	`define	J2
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	192'h0D0C0B0A0908050403020100000000000000000000000000
	`define	in_ENC_TEST 	96'h2072616C6C69702065687420
	`define	in_DEC_TEST	96'h602807A462b469063D8FF082
	`define	in_iKEY_TEST	8'hE5
	`define	in_iENC_TEST	8'hC5
	`define	in_iDEC_TEST	8'h85

	`define	out_ENC_TEST	96'h602807A462b469063D8FF082
	`define	out_DEC_TEST	96'h2072616C6C69702065687420
	`define out_iKEY_TEST	8'hF5
	`define	out_iENC_TEST	8'hD5
	`define	out_iDEC_TEST	8'h95
`else `ifdef MODE6
	`define	MODE	6
	`define	N	48
	`define	M	3
	`define	T	54
	`define	J3
	`define	Cb	6

	//	TEST VECTORS
	`define	in_KEY_TEST	192'h1514131211100D0C0B0A09080504030201000000000000000
	`define	in_ENC_TEST 	96'h74616874207473756420666f
	`define	in_DEC_TEST	96'hECAD1C6C451E3f59C5DB1AE9
	`define	in_iKEY_TEST	8'hE6
	`define	in_iENC_TEST	8'hC6
	`define	in_iDEC_TEST	8'h86

	`define	out_ENC_TEST	96'hECAD1C6C451E3f59C5DB1AE9
	`define	out_DEC_TEST	96'h74616874207473756420666f
	`define out_iKEY_TEST	8'hF6
	`define	out_iENC_TEST	8'hD6
	`define	out_iDEC_TEST	8'h96
`else `ifdef MODE7
	`define	MODE	7
	`define	N	64
	`define	M	2
	`define	T	68
	`define	J2
	`define	Cb	7

	//	TEST VECTORS
	`define	in_KEY_TEST	256'h0F0E0D0C0B0A0908070605040302010000000000000000000000000000000000
	`define	in_ENC_TEST 	128'h63736564207372656C6C657661727420
	`define	in_DEC_TEST	128'h49681B1E1E54FE3F65AA832AF84E0BBC
	`define	in_iKEY_TEST	8'hE7
	`define	in_iENC_TEST	8'hC7
	`define	in_iDEC_TEST	8'h87

	`define	out_ENC_TEST	128'h49681B1E1E54FE3F65AA832AF84E0BBC
	`define	out_DEC_TEST	128'h63736564207372656C6C657661727420
	`define out_iKEY_TEST	8'hF7
	`define	out_iENC_TEST	8'hD7
	`define	out_iDEC_TEST	8'h97
`else `ifdef MODE8
	`define	MODE	8
	`define	N	64
	`define	M	3
	`define	T	69
	`define	J3
	`define	Cb	7

	//	TEST VECTORS
	`define	in_KEY_TEST	256'h17161514131211100F0E0D0C0B0A090807060504030201000000000000000000
	`define	in_ENC_TEST 	128'h206572656874206E6568772065626972
	`define	in_DEC_TEST	128'hC4AC61EFFCDC0D4F6C9C8D6E2597b85B
	`define	in_iKEY_TEST	8'hE8
	`define	in_iENC_TEST	8'hC8
	`define	in_iDEC_TEST	8'h88

	`define	out_ENC_TEST	128'hC4AC61EFFCDC0D4F6C9C8D6E2597b85B
	`define	out_DEC_TEST	128'h206572656874206E6568772065626972
	`define out_iKEY_TEST	8'hF8
	`define	out_iENC_TEST	8'hD8
	`define	out_iDEC_TEST	8'h98
`else `ifdef MODE9
	`define	MODE	9
	`define	N	64
	`define	M	4
	`define	M4
	`define	T	72
	`define	J4
	`define	Cb	7

	//	TEST VECTORS
	`define	in_KEY_TEST	256'h1F1E1D1C1B1A191817161514131211100F0E0D0C0B0A09080706050403020100
	`define	in_ENC_TEST 	128'h74206E69206D6F6F6D69732061207369
	`define	in_DEC_TEST	128'h8D2B5579AFC8A3A03BF72A87EfE7B868
	`define	in_iKEY_TEST	8'hE9
	`define	in_iENC_TEST	8'hC9
	`define	in_iDEC_TEST	8'h89

	`define	out_ENC_TEST	128'h8D2B5579AFC8A3A03BF72A87EfE7B868
	`define	out_DEC_TEST	128'h74206E69206D6F6F6D69732061207369
	`define out_iKEY_TEST	8'hF9
	`define	out_iENC_TEST	8'hD9
	`define	out_iDEC_TEST	8'h99
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