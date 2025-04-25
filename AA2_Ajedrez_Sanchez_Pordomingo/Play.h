#pragma once
#include "Library.h"
#include "utils.h"

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos, int jugador);

bool comprobarJaque(std::vector<Pieces>& listPiecesPos, int jugador);

void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos);

void updateChessboard(std::vector<Pieces> listPiecePos, char chessboard[BOARD_SIZE][BOARD_SIZE]);

void movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador);

bool comprobarTablas(std::vector<Pieces> listPiecesPos, int jugador);

bool playerOwnsPiece(int x, int y, std::vector<Pieces> listPiecePos, int jugador);