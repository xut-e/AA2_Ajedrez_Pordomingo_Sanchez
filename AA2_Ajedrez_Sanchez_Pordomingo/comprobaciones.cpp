#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"

void piezaEnMedio() {

}

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos, int jugador) {
	return false;
}

bool comprobarJaque(std::vector<Pieces>& listPiecesPos, int jugador) {
	return false;
}


bool comprobarTablas(std::vector<Pieces> listPiecesPos, int jugador) {
	return false;
}


//Funcion para comprobar si al jugador le pertenece la pieza que hay en la casilla que ha seleccionado
bool playerOwnsPiece(int x, int y, std::vector<Pieces> listPiecePos, int jugador, int& idPieza) {

	for (int i = 0; i < TOTAL_PIECES; i++)
	{
		Pieces pieza = listPiecePos[i];
		if (pieza.active && pieza.pos.x == x && pieza.pos.y == y)
		{
			idPieza = i;

			if (jugador == JUGADOR1)
			{
				if (!(i >= 16 && i <= 31))
				{
					std::cout << "Esa pieza no es tuya!" << std::endl;
				}
				return (i >= 16 && i <= 31);
			}
			else
			{
				if (!(i >= 0 && i <= 15))
				{
					std::cout << "Esa pieza no es tuya!" << std::endl;
				}
				return (i >= 0 && i <= 15);
			}
		}
	}

	std::cout << "No hay ninguna pieza ahi!" << std::endl;

	return false;
}

void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido) {
	
	int idPiezaComida, x, y;
	
	std::cout << "Introduce la casilla a la que moveras (fila y columna): ";

	do
	{
		movimientoValido = true;

		std::cin >> x >> y;

		x = 8 - x;
		y -= 1;

		for (int i = 0; i < listPiecePos.size(); i++)
		{
			if (listPiecePos[i].pos.x == x && listPiecePos[i].pos.y == y)
			{
				comer = true;
				idPiezaComida = i;
				break;
			}
		}

		if (jugador == JUGADOR1 && comer)
		{
			if (idPiezaComida >= 16 && idPiezaComida <= 31)
			{
				movimientoValido = false;
			}
		}
		else if (jugador == JUGADOR2 && comer)
		{
			if (idPiezaComida >= 0 && idPiezaComida <= 15)
			{
				movimientoValido = false;
			}
		}

		if (!movimientoValido)
		{
			std::cout << "No puedes mover ahi!" << std::endl;
			continue;
		}






		if (listPiecePos[idPieza].piece == BLACK_PAWN)
		{
			if (comer)
			{
				if (x == listPiecePos[idPieza].pos.x + 1 && (y == listPiecePos[idPieza].pos.y - 1 || y == listPiecePos[idPieza].pos.y + 1))
				{
					movimientoValido = true;
				}
			}
			else if (x == listPiecePos[idPieza].pos.x + 1 && y == listPiecePos[idPieza].pos.y)
			{
				movimientoValido = true;
			}
			else if (listPiecePos[idPieza].pos.x == 1)
			{
				if (x == listPiecePos[idPieza].pos.x + 2 && y == listPiecePos[idPieza].pos.y)
				{
					movimientoValido = true;
				}
			}
			else
			{
				movimientoValido = false;
			}

		}
		else if (listPiecePos[idPieza].piece == WHITE_PAWN)
		{
			if (comer)
			{
				if (x == listPiecePos[idPieza].pos.x - 1 && (y == listPiecePos[idPieza].pos.y - 1 || y == listPiecePos[idPieza].pos.y + 1))
				{
					movimientoValido = true;
				}
			}
			else if ((x == listPiecePos[idPieza].pos.x - 1 && y == listPiecePos[idPieza].pos.y))
			{
				movimientoValido = true;
			}
			else if (listPiecePos[idPieza].pos.x == 6)
			{
				if (x == listPiecePos[idPieza].pos.x - 2 && y == listPiecePos[idPieza].pos.y)
				{
					movimientoValido = true;
				}
			}
			else
			{
				movimientoValido = false;
			}
		}
		else if (listPiecePos[idPieza].piece == BLACK_ROOK || listPiecePos[idPieza].piece == WHITE_ROOK)
		{
			if (x == listPiecePos[idPieza].pos.x && (y > listPiecePos[idPieza].pos.y || y < listPiecePos[idPieza].pos.y) || y == listPiecePos[idPieza].pos.y && (x < listPiecePos[idPieza].pos.x || x > listPiecePos[idPieza].pos.x))
			{
				movimientoValido = true;
			}
			else
			{
				movimientoValido = false;
			}
		}
		else if (listPiecePos[idPieza].piece == BLACK_KNIGHT || listPiecePos[idPieza].piece == WHITE_KNIGHT)
		{

		}
		else if (listPiecePos[idPieza].piece == BLACK_BISHOP || listPiecePos[idPieza].piece == WHITE_BISHOP)
		{

		}
		else if (listPiecePos[idPieza].piece == BLACK_KING || listPiecePos[idPieza].piece == WHITE_KING)
		{

		}
		else if (listPiecePos[idPieza].piece == BLACK_QUEEN || listPiecePos[idPieza].piece == WHITE_QUEEN)
		{

		}
	} while (!movimientoValido);
}