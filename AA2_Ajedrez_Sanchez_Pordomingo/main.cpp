#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "Play.h"
#include "Init.h"

//Funcion principal de ejecucion del juego
int main() {
	char chessboard[BOARD_SIZE][BOARD_SIZE];

	//Inicializamos teclado y las listas de piezas y posiciones para unirlas en listPiecePos
	initChessBoard(chessboard);
	std::vector<char> pieceList = initPieces();
	std::vector<Position> initialPos = initPosPieces(pieceList);
	std::vector<Pieces> listPiecePos = initPieceList(pieceList, initialPos);
	
	//Actualizamos el tablero por primera vez (debug)
	updateChessboard(listPiecePos,chessboard);
	
	//Imprimimos el tablero por primera vez (debug)
	viewChessBoard(chessboard);

	//Iniciamos el juego (ir a play.cpp)
	play(chessboard, listPiecePos);
}



//La lista de piezas se ve asi: thbqkbhtppppppppTHBKQBHTPPPPPPPP

/*La listPiecePos se ve asi :

		[0 ]	{piece=116 't' pos={x=0 y=0 } }	
		[1] 	{piece=104 'h' pos={x=0 y=1 } }	
		[2] 	{piece=98 'b' pos={x=0 y=2 } }	
		[3]   	{piece=113 'q' pos={x=0 y=3 } }	
		[4]	    {piece=107 'k' pos={x=0 y=4 } }	
		[5]    	{piece=98 'b' pos={x=0 y=5 } }	
		[6]	    {piece=104 'h' pos={x=0 y=6 } }	
		[7]	    {piece=116 't' pos={x=0 y=7 } }	
		[8]	    {piece=112 'p' pos={x=1 y=0 } }	
		[9]	    {piece=112 'p' pos={x=1 y=1 } }	
		[10]	{piece=112 'p' pos={x=1 y=2 } }	
		[11]	{piece=112 'p' pos={x=1 y=3 } }	
		[12]	{piece=112 'p' pos={x=1 y=4 } }	
		[13]	{piece=112 'p' pos={x=1 y=5 } }	
		[14]	{piece=112 'p' pos={x=1 y=6 } }	
		[15]	{piece=112 'p' pos={x=1 y=7 } }	
		[16]	{piece=84 'T' pos={x=7 y=0 } }	
		[17]	{piece=72 'H' pos={x=7 y=1 } }	
		[18]	{piece=66 'B' pos={x=7 y=2 } }	
		[19]	{piece=75 'K' pos={x=7 y=3 } }	
		[20]	{piece=81 'Q' pos={x=7 y=4 } }	
		[21]	{piece=66 'B' pos={x=7 y=5 } }	
		[22]	{piece=72 'H' pos={x=7 y=6 } }	
		[23]	{piece=84 'T' pos={x=7 y=7 } }	
		[24]	{piece=80 'P' pos={x=6 y=0 } }	
		[25]	{piece=80 'P' pos={x=6 y=1 } }	
		[26]	{piece=80 'P' pos={x=6 y=2 } }	
		[27]	{piece=80 'P' pos={x=6 y=3 } }	
		[28]	{piece=80 'P' pos={x=6 y=4 } }	
		[29]	{piece=80 'P' pos={x=6 y=5 } }	
		[30]	{piece=80 'P' pos={x=6 y=6 } }	
		[31]	{piece=80 'P' pos={x=6 y=7 } }	

*/