#pragma once
#include "Library.h"
#include "utils.h"


bool menuMovimiento();

bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador);

void movimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& movimientoValido);

void cambiarPosicion(int idPieza, Position casillaFinal, std::vector<Pieces>& listPiecePos);
