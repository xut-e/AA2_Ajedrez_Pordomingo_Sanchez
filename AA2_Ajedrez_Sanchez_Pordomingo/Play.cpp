#include "Library.h"
#include "utils.h"
#include "Const.h"

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos) {
	return false;
}

void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos) {
	while (!comprobarJaqueMate(listPiecesPos))
	{
		for (int i = 0; i < Jugadores; i++)
		{
			//Logica de turnos
		}
	}
}

void updateChessboard(std::vector<Pieces> listPiecePos, char chessboard[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < TOTAL_PIECES; i++)
	{
		chessboard[listPiecePos[i].pos.x][listPiecePos[i].pos.y] = listPiecePos[i].piece;
	}
	
}