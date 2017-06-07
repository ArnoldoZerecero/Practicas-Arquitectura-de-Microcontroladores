`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Universidad Aut�noma de Guadalajara
// Engineer: Jes�s Arnoldo Zerecero N��ez, Andrea Alejandra Mondrag�n Olivos
// 
// Create Date:    17:21:03 06/03/2017 
// Design Name: 
// Module Name:    ALU 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module ALU(
input [3:0] ivInstruccion,
input [3:0] ivRegistroA,
input [3:0] ivRegistroB,
output [3:0] ovResultado,
output [3:0] ovFlags
    );

reg [3:0] rvResultado = 4'b0000;
reg [3:0] rvFlags = 4'b0000;

assign ovResultado = rvResultado;
assign ovFlags = rvFlags;

localparam [3:0] INS_ADD = 4'b0000;
localparam [3:0] INS_SUB = 4'b0001;
localparam [3:0] INS_AND = 4'b0010;
localparam [3:0] INS_OR = 4'b0011;
localparam [3:0] INS_XOR = 4'b0100;
localparam [3:0] INS_NAND = 4'b0101;
localparam [3:0] INS_NOR = 4'b0110;
localparam [3:0] INS_XNOR = 4'b0111;
localparam [3:0] INS_NOT = 4'b1000;
localparam [3:0] INS_LSHIFT = 4'b1001;
localparam [3:0] INS_RSHIFT = 4'b1010;

always @*
begin
case(ivInstruccion)
	INS_ADD: 
	begin
		rvResultado = ivRegistroA + ivRegistroB;
	/*C*/
		if (ivRegistroA + ivRegistroB >= 5'b10000) /*Si el resultado necesita m�s de 4 bits de espacio*/
		begin
			rvFlags[1] = 1'b1; /*Se prende la bandera C*/
		end
		else
		begin
			rvFlags[1] = 1'b0; /*No se prende la bandera C*/
		end
	/*V*/
		rvFlags[0] = (rvResultado[3] ^ ivRegistroA[3]) & (rvResultado[3] ^ ivRegistroB[3]); /*Si el MSB del resultado es diferente a ambos MSB de las entradas, se prende la bandera de overflow (XOR da 1 si son diferentes, AND mide si el resultado es diferente a ambos y entrega un 1)*/
	end
	INS_SUB: 
	begin
		rvResultado = ivRegistroA - ivRegistroB;
	/*C*/
		if (ivRegistroA - ivRegistroB >= 5'b10000) /*Si el resultado necesita m�s de 4 bits de espacio*/
		begin
				rvFlags[1] = 1'b1; /*Se prende la bandera C*/
		end
		else
		begin
				rvFlags[1] = 1'b0; /*No se prende la bandera C*/
		end
	/*V*/
		rvFlags[0] = (ivRegistroA[3] ^ ivRegistroB[3]) & (ivRegistroA[3] ^ rvResultado[3]); /*So el MSB del primer registro es diferente al del segundo registro y al del resultado*/
	end
	INS_AND: 
	begin
		rvResultado	= ivRegistroA & ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_OR: 
	begin 
		rvResultado = ivRegistroA | ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_XOR:
	begin
		rvResultado = ivRegistroA ^ ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_NAND: 
	begin
		rvResultado = ~(ivRegistroA & ivRegistroB);
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_NOR: 
	begin
		rvResultado =  ~(ivRegistroA | ivRegistroB);
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_XNOR: 
	begin
		rvResultado = ivRegistroA ~^ ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_NOT: 
	begin
		rvResultado = ~ivRegistroA;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_LSHIFT: 
	begin
		rvResultado = ivRegistroA<<ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	INS_RSHIFT: 
	begin
		rvResultado = ivRegistroA>>ivRegistroB;
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
	default: 
	begin
		rvResultado = 4'b0000; /*En caso de que la instrucci�n no exista*/
		rvFlags[1:0] = 2'b00; /*No se utilizan las banderas de carry y overflow*/
	end
endcase
/*Z*/
	rvFlags[3] = ~(|rvResultado); /*Se realiza una NOR entre cada bit del resultado, la OR otorga un 1 si cualquier bit es uno, asi que ahora otorgar� 0 y la bandera solo se prendera cuando ningun bit sea 1*/
/*N*/		
	rvFlags[2] = rvResultado[3]; /*La bandera adquiere el valor del MSB: 1 si es negativo o 0 si es positivo*/
end

endmodule
