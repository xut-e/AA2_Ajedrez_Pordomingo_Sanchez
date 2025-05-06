#pragma once
#include "Library.h"
#include "utils.h"


bool menuMovimiento();

bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador, int& contador50Movimientos);

void movimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& movimientoValido, Position& casillaFinal, bool& comer, bool& enroque, int& contador50Movimientos);

void cambiarPosicion(int idPieza, Position casillaFinal, std::vector<Pieces>& listPiecePos, bool& enroque);

void cambiarPieza(std::vector<Pieces>& listPiecePos, int idPieza, char piezaElegida);
