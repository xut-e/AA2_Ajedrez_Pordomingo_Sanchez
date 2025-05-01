#pragma once
#include "Library.h"
#include "utils.h"

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos, int jugador);

bool comprobarJaque(std::vector<Pieces>& listPiecesPos, int jugador);

bool comprobarTablas(std::vector<Pieces> listPiecesPos, int jugador);

bool playerOwnsPiece(int x, int y, std::vector<Pieces> listPiecePos, int jugador, int& idPieza);

void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido);

bool piezaEnMedio(Position casillaInicial, Position casillaFinal, char pieza, std::vector<Pieces> listPiecePos, bool comer, bool salidaMaxima);

bool casillaAtacada(int x, int y);