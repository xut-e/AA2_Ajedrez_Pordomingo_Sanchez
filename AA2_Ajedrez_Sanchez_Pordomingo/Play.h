#pragma once
#include "Library.h"
#include "utils.h"

void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos);

void updateChessboard(std::vector<Pieces> listPiecePos, char chessboard[BOARD_SIZE][BOARD_SIZE]);

std::string obtenerClaveTablero(std::vector<Pieces>& listPiecePos, int jugador);