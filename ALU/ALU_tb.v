`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   00:52:56 06/06/2017
// Design Name:   ALU
// Module Name:   D:/Documents/UAG/ISE/ALU/ALU_tb.v
// Project Name:  ALU
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: ALU
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module ALU_tb;

	// Inputs
	reg [3:0] ivInstruccion;
	reg [3:0] ivRegistroA;
	reg [3:0] ivRegistroB;

	// Outputs
	wire [3:0] ovResultado;
	wire [3:0] ovFlags;

	// Instantiate the Unit Under Test (UUT)
	ALU uut (
		.ivInstruccion(ivInstruccion), 
		.ivRegistroA(ivRegistroA), 
		.ivRegistroB(ivRegistroB), 
		.ovResultado(ovResultado), 
		.ovFlags(ovFlags)
	);

	initial begin
		// Initialize Inputs
		ivInstruccion = 4'b0000;
		ivRegistroA = 4'b0000;
		ivRegistroB = 4'b0000;
	forever
	begin
		ivInstruccion = $random%4'b1010;
		ivRegistroA = $random%4'b1111;
		ivRegistroB = $random%4'b1111;
		#10;
	end
		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

