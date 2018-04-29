`include "SIMON_defintions.svh"

module test_SIMON_topPKT;

//	INPUTS
logic				clk, nR;
logic				in_newPKT;
logic				out_readPKT;
logic [(1+(`N/2)):0][7:0]	in;

//	OUTPUTS
logic 				in_loadPKT, in_donePKT;
logic				out_donePKT;
logic [(1+(`N/2)):0][7:0]	out;

logic [7:0] 			info, countOUT;
logic [1:0][1:0][`N-1:0] 	block;

assign block[0] = 		out[(`N/4)-1:0];
assign block[1] = 		out[(`N/2)-1:(`N/4)];
assign countOUT = 		out[(`N/2)];
assign info = 			out[(`N/2)+1];

SIMON_topPKT			topPKT(.*);

logic				encrypt, encryptPASS, decryptPASS, doneSIM;
assign doneSIM = 		encryptPASS && decryptPASS;
logic [7:0]			countPKT;

initial
begin
	#50ns		clk = 1'b0;
	forever #50ns	clk = ~clk;
end

initial
begin
	nR = 1'b0;	
	@(posedge clk);
	#10ns
	
	in_newPKT = 1'b0;
	out_readPKT = 1'b0;
	encrypt = 1'b1;
	encryptPASS =1'b0;
	decryptPASS = 1'b0;
	countPKT = 8'h00;
	in = {`in_iKEY_TEST, 8'h00, `in_KEY_TEST };

	@(posedge clk);
	#10ns

	nR = 1'b1;

	@(posedge clk);
	#10ns
	
	in_newPKT <= 1'b1;
end

always @(posedge in_loadPKT)
begin
	repeat(2)	@(posedge clk);
	#10ns
	
	if(~doneSIM)	countPKT <= countPKT + 1'b1;
	in_newPKT <= 1'b0;
end

always @(posedge in_donePKT)
begin
	repeat(2)	@(posedge clk);
	#10ns

	if(~doneSIM)
	begin
		if(encrypt)	in <= { `in_iENC_TEST, countPKT, `in_ENC_TEST, `in_ENC_TEST};
		else		in <= { `in_iDEC_TEST, countPKT, `in_DEC_TEST, `in_DEC_TEST};
	
		@(posedge clk)
		#10ns
		in_newPKT <= 1'b1;
		encrypt <= ~encrypt;
	end
end

always @(posedge out_donePKT)
begin
	repeat(2)	@(posedge clk);

	$display("READING PACKET @", $time);
	if(~info[5])
	begin
		$display("DATA PACKET");
		if(info[6] && (block[0] == `out_ENC_TEST))
		begin
			encryptPASS = 1'b1;
			$display("ENCRYPTION PASS @", $time);
		end
		else if(~info[6] && (block[0] == `out_DEC_TEST))
		begin
			decryptPASS = 1'b1;
			$display("DECRYPTION PASS @", $time);
		end
	end
	else	$display("KEY PACKET");

	#10ns
	
	out_readPKT <= 1'b1;

	repeat(2)	@(posedge clk);
	#10ns

	out_readPKT <= 1'b0;

	if(doneSIM)	$finish;
end

endmodule
