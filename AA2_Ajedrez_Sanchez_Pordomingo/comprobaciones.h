#pragma once
#include "Library.h"
#include "utils.h"

bool jaqueMate(std::vector<Pieces>& listPiecesPos, int jugador);

bool jaque(std::vector<Pieces>& listPiecesPos, int jugador);

bool tablas(std::vector<Pieces> listPiecesPos, int jugador, int& contador50Movimientos, std::vector<std::string>& historialPosiciones, int& tipoTablas);

bool playerOwnsPiece(int x, int y, std::vector<Pieces> listPiecePos, int jugador, int& idPieza);

void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido, Position& casillaFinal, bool& enroque, int& contador50Movimientos);

bool piezaEnMedio(Position casillaInicial, Position casillaFinal, char pieza, std::vector<Pieces> listPiecePos, bool comer, bool salidaMaxima);

bool casillaAtacada(Position& casillaAComprobar, int jugadorAtacante, std::vector<Pieces> listPiecePos);

bool puedeAtacar(Position& posPieza, char tipoPieza, Position& casillaObjetivo, std::vector<Pieces>& listPiecePos);

bool caminoDespejado(Position casillaInicial, Position casillaFinal, std::vector<Pieces>& listPiecePos, int jugadorAtacante);

bool coronacion(std::vector<Pieces>& listPiecePos, int jugador, int& idPieza);

bool tablasPorAhogado(std::vector<Pieces> listPiecePos, int jugador);

bool tablasPorFaltadeMaterial(std::vector<Pieces> listPiecePos);

bool tablasPorRepeticion(std::vector<std::string>& historialPosiciones);

bool tablasPor50Movimientos(int& contador50Movimentos);

bool tieneMovimientosLegales(std::vector<Pieces>& listPiecePos, int i);