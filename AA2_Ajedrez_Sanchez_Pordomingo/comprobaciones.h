#pragma once
#include "Library.h"
#include "utils.h"

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos, int jugador);

bool comprobarJaque(std::vector<Pieces>& listPiecesPos, int jugador);

bool comprobarTablas(std::vector<Pieces> listPiecesPos, int jugador);

bool playerOwnsPiece(int x, int y, std::vector<Pieces> listPiecePos, int jugador, int& idPieza);

