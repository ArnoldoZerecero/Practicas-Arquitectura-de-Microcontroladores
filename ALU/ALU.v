`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: Universidad Autónoma de Guadalajara
// Engineer: Jesús Arnoldo Zerecero Núñez, Andrea Alejandra Mondragón Olivos
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
	INS_ADD: rvResultado = ivRegistroA + ivRegistroB;
	INS_SUB: rvResultado = ivRegistroA - ivRegistroB;
	INS_AND: rvResultado	= ivRegistroA & ivRegistroB;
	INS_OR: rvResultado = ivRegistroA | ivRegistroB;
	INS_XOR: rvResultado = ivRegistroA ^ ivRegistroB;
	INS_NAND: rvResultado = ~(ivRegistroA & ivRegistroB);
	INS_NOR: rvResultado =  ~(ivRegistroA | ivRegistroB);
	INS_XNOR: rvResultado = ivRegistroA ~^ ivRegistroB;
	INS_NOT: rvResultado = ~ivRegistroA;
	INS_LSHIFT: rvResultado = ivRegistroA<<ivRegistroB;
	INS_RSHIFT: rvResultado = ivRegistroA>>ivRegistroB;
	default: rvResultado = 4'b0000; /*En caso de que la instrucción no exista*/
endcase
/*Z*/
	if (rvResultado == 4'b0)/*Si el resultado es cero*/
		begin
			rvFlags[3] = 1'b1; /*Se prende la bandera Z*/
		end
	else
		begin
			rvFlags[3] = 1'b0; /*No se prende la bandera Z*/
		end
/*N*/		
	if (rvResultado[3] == 4'b1) /*Si el MSB es 1, el resultado es negativo*/
		begin
			rvFlags[2] = 1'b1; /*Se prende la bandera N*/
		end
	else
		begin
			rvFlags[2] = 1'b0; /*No se prende la bandera N*/
		end
/*C y V*/		
	if (ivInstruccion == INS_ADD) /*Si se está realizando una suma*/
	begin
	/*C*/
		if (ivRegistroA + ivRegistroB >= 5'b10000) /*Si el resultado necesita más de 4 bits de espacio*/
			begin
				rvFlags[1] = 1'b1; /*Se prende la bandera C*/
			end
		else
			begin
				rvFlags[1] = 1'b0; /*No se prende la bandera C*/
			end
	/*V*/
		if(ivRegistroA[3] == 1'b1 && ivRegistroB[3] == 1'b1 && rvResultado[3] == 1'b0) /*Si los MSB de las entradas son 1 y el resultado es 0*/
			begin
				rvFlags[0] = 1'b1; /*Se prende la bandera V*/
			end
		else if (ivRegistroA[3] == 1'b0 && ivRegistroB[3] == 1'b0 && rvResultado[3] == 1'b1) /*Si los MSB de las entradas son 0 y el resultado es 1*/
			begin
				rvFlags[0] = 1'b1; /*Se prende la bandera V*/
			end
		else
			begin
				rvFlags[0] = 1'b0; /*No se prende la bandera V*/
			end
	end
	else if (ivInstruccion == INS_SUB) /*Si se está realizando una resta*/
	begin
	/*C*/
		if (ivRegistroA - ivRegistroB >= 5'b10000) /*Si el resultado necesita más de 4 bits de espacio*/
			begin
				rvFlags[1] = 1'b1; /*Se prende la bandera C*/
			end
		else
			begin
				rvFlags[1] = 1'b0; /*No se prende la bandera C*/
			end
	/*V*/
		if((ivRegistroA[3] == 1'b0) && (ivRegistroB[3] == 1'b1) && (rvResultado[3] == 1'b1)) /*Si se resta positivo menos negativo y el resultado es negativo*/
			begin
				rvFlags[0] = 1'b1; /*Se prende la bandera V*/
			end
		else if ((ivRegistroA[3] == 1'b1) && (ivRegistroB[3] == 1'b0) && (rvResultado[3] == 1'b0)) /*Si se resta negativo menos positivo y el resultado es positivo*/
			begin
				rvFlags[0] = 1'b1; /*Se prende la bandera V*/
			end
		else
			begin
				rvFlags[0] = 1'b0; /*No se prende la bandera V*/
			end
	end
	else
		begin
			rvFlags[1:0] = 2'b00; /*No se realizó una suma ni una resta, las banderas C y V no se utilizan*/
		end
end

endmodule
