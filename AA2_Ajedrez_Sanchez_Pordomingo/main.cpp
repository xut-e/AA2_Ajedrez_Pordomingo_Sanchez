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

		[0 ]	{piece=116 't' pos={x=0 y=0 } active=true }	
		[1] 	{piece=104 'h' pos={x=0 y=1 } active=true }	
		[2] 	{piece=98 'b' pos={x=0 y=2 } active=true }	
		[3]   	{piece=113 'q' pos={x=0 y=3 } active=true }	
		[4]	    {piece=107 'k' pos={x=0 y=4 } active=true }	
		[5]    	{piece=98 'b' pos={x=0 y=5 } active=true }	
		[6]	    {piece=104 'h' pos={x=0 y=6 } active=true }	
		[7]	    {piece=116 't' pos={x=0 y=7 } active=true }	
		[8]	    {piece=112 'p' pos={x=1 y=0 } active=true }	
		[9]	    {piece=112 'p' pos={x=1 y=1 } active=true }	
		[10]	{piece=112 'p' pos={x=1 y=2 } active=true }	
		[11]	{piece=112 'p' pos={x=1 y=3 } active=true }	
		[12]	{piece=112 'p' pos={x=1 y=4 } active=true }	
		[13]	{piece=112 'p' pos={x=1 y=5 } active=true }	
		[14]	{piece=112 'p' pos={x=1 y=6 } active=true }	
		[15]	{piece=112 'p' pos={x=1 y=7 } active=true }	
		[16]	{piece=84 'T' pos={x=7 y=0 } active=true }	
		[17]	{piece=72 'H' pos={x=7 y=1 } active=true }	
		[18]	{piece=66 'B' pos={x=7 y=2 } active=true }	
		[19]	{piece=75 'K' pos={x=7 y=3 } active=true }	
		[20]	{piece=81 'Q' pos={x=7 y=4 } active=true }	
		[21]	{piece=66 'B' pos={x=7 y=5 } active=true }	
		[22]	{piece=72 'H' pos={x=7 y=6 } active=true }	
		[23]	{piece=84 'T' pos={x=7 y=7 } active=true }	
		[24]	{piece=80 'P' pos={x=6 y=0 } active=true }	
		[25]	{piece=80 'P' pos={x=6 y=1 } active=true }	
		[26]	{piece=80 'P' pos={x=6 y=2 } active=true }	
		[27]	{piece=80 'P' pos={x=6 y=3 } active=true }	
		[28]	{piece=80 'P' pos={x=6 y=4 } active=true }	
		[29]	{piece=80 'P' pos={x=6 y=5 } active=true }	
		[30]	{piece=80 'P' pos={x=6 y=6 } active=true }	
		[31]	{piece=80 'P' pos={x=6 y=7 } active=true }	

*/