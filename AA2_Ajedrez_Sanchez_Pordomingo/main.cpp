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