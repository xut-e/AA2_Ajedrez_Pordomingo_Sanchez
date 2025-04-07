#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "Play.h"
#include "Init.h"

int main() {
	char chessboard[BOARD_SIZE][BOARD_SIZE];

	initChessBoard(chessboard);
	std::vector<char> pieceList = initPieces();
	std::vector<Position> initialPos = initPosPieces(pieceList);
	std::vector<Pieces> listPiecePos = initPieceList(pieceList, initialPos);

	updateChessboard(listPiecePos,chessboard);
	
	viewChessBoard(chessboard);

	//play(chessboard, listPiecePos);
}