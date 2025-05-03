#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "moves.h"

//A casi toda esta función me ha ayudado la IA, mis implementaciones no funcionaban bien siempre, pero entiendo perfectamente lo que está haciendo y el uso de operadores ternarios
bool piezaEnMedio(Position casillaInicial, Position casillaFinal, char pieza,std::vector<Pieces> listPiecePos, bool comer, bool salidaMaxima) {

	if (pieza == WHITE_ROOK || pieza == BLACK_ROOK || pieza == WHITE_QUEEN || pieza == BLACK_QUEEN || ((pieza == WHITE_PAWN || pieza == BLACK_PAWN) && !comer && salidaMaxima))
	{

		if (casillaInicial.y == casillaFinal.y) 
		{
			int step = (casillaFinal.x > casillaInicial.x) ? 1 : -1;

			for (int i = casillaInicial.x + step; i != casillaFinal.x; i += step) 
			{
				for (size_t j = 0; j < listPiecePos.size(); j++) 
				{
					if (listPiecePos[j].active && listPiecePos[j].pos.x == i && listPiecePos[j].pos.y == casillaInicial.y) 
					{
						return true;
					}
				}
			}
		}

		else if (casillaInicial.x == casillaFinal.x) 
		{
			int step = (casillaFinal.y > casillaInicial.y) ? 1 : -1;

			for (int i = casillaInicial.y + step; i != casillaFinal.y; i += step) 
			{
				for (size_t j = 0; j < listPiecePos.size(); j++) 
				{
					if (listPiecePos[j].active && listPiecePos[j].pos.y == i && listPiecePos[j].pos.x == casillaInicial.x) 
					{
						return true;
					}
				}
			}
		}
	}

	if (pieza == WHITE_BISHOP || pieza == BLACK_BISHOP || pieza == WHITE_QUEEN || pieza == BLACK_QUEEN)
	{
		int deltaX = abs(casillaFinal.x - casillaInicial.x), deltaY = abs(casillaFinal.y - casillaInicial.y);

		if (deltaX == deltaY && deltaX > 0)
		{
			int stepX = (casillaFinal.x > casillaInicial.x) ? 1 : -1, stepY = (casillaFinal.y > casillaInicial.y) ? 1 : -1;

			for (int i = 1; i < deltaX; i++)
			{
				int checkX = casillaInicial.x + i * stepX;
				int checkY = casillaInicial.y + i * stepY;

				for (size_t j = 0; j < listPiecePos.size(); j++)
				{
					if (listPiecePos[j].active && listPiecePos[j].pos.x == checkX && listPiecePos[j].pos.y == checkY)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
	
}

bool casillaAtacada(int x, int y) {
	return false;
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

//Las comprobaciones referentes a los peones y al alfil me ha ayudado la IA. Estoy pensando si cambiar el resto para hacerlo más limpio, me he fijado que en vez de usar ifs camba movimientoValido por la comparación, lo que obtiene el mismo resultado más limpio.
void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido, Position& casillaFinal) {
	
	int idPiezaComida, x, y;
	bool salidaMaxima = false;

	Position casillaInicial = { listPiecePos[idPieza].pos.x, listPiecePos[idPieza].pos.y };
	
	
	std::cout << "Introduce la casilla a la que moveras (fila y columna): ";

	do
	{
		movimientoValido = true;

		do
		{
			std::cin >> x >> y;

			x = 8 - x;
			y -= 1;

			if (!(x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE))
			{
				std::cout << "Esa casilla no existe en el tablero, selecciona una entre (1-8, 1-8): ";
			}
		} while (!(x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE));
		

		casillaFinal = { x,y };

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

		if (movimientoValido)
		{
			if (listPiecePos[idPieza].piece == BLACK_PAWN) {
				if (comer) 
				{
					// Captura en diagonal (1 casilla)
					movimientoValido = ((x == casillaInicial.x + 1) && (abs(y - casillaInicial.y) == 1));
				}
				else {
					// Movimiento hacia adelante
					if (x == casillaInicial.x + 1 && y == casillaInicial.y) 
					{
						movimientoValido = !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima);
					}
					// Movimiento inicial de 2 casillas
					else if (casillaInicial.x == 1 && x == casillaInicial.x + 2 && y == casillaInicial.y) 
					{
						movimientoValido = !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima);
					}
					else 
					{
						movimientoValido = false;
					}
				}
			}
			// Movimiento de peón blanco (similar pero en dirección opuesta)
			else if (listPiecePos[idPieza].piece == WHITE_PAWN) {
				if (comer) 
				{
					movimientoValido = (x == casillaInicial.x - 1) && (abs(y - casillaInicial.y) == 1);
				}
				else 
				{
					if (x == casillaInicial.x - 1 && y == casillaInicial.y) 
					{
						movimientoValido = !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima);
					}
					else if (casillaInicial.x == 6 && x == casillaInicial.x - 2 && y == casillaInicial.y) 
					{
						movimientoValido = !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima);
					}
					else 
					{
						movimientoValido = false;
					}
				}
			}
			// Movimiento del alfil
			else if (listPiecePos[idPieza].piece == BLACK_BISHOP || listPiecePos[idPieza].piece == WHITE_BISHOP)
			{
				int deltaX = abs(x - casillaInicial.x);
				int deltaY = abs(y - casillaInicial.y);

				if (deltaX == deltaY && deltaX > 0)
				{
					movimientoValido = (deltaX == deltaY && deltaX > 0) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima);
				}
				else
				{
					movimientoValido = false;
				}
			}

			else if (listPiecePos[idPieza].piece == BLACK_ROOK || listPiecePos[idPieza].piece == WHITE_ROOK)
			{
				if (((x == listPiecePos[idPieza].pos.x && (y > listPiecePos[idPieza].pos.y || y < listPiecePos[idPieza].pos.y)) || (y == listPiecePos[idPieza].pos.y && (x < listPiecePos[idPieza].pos.x || x > listPiecePos[idPieza].pos.x))) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
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
				if ((x == listPiecePos[idPieza].pos.x + 2 && (y == listPiecePos[idPieza].pos.y + 1 || y == listPiecePos[idPieza].pos.y - 1)) || (x == listPiecePos[idPieza].pos.x - 2 && (y == listPiecePos[idPieza].pos.y + 1 || y == listPiecePos[idPieza].pos.y - 1)) || (x == listPiecePos[idPieza].pos.x + 1 && (y == listPiecePos[idPieza].pos.y + 2 || y == listPiecePos[idPieza].pos.y - 2)) || (x == listPiecePos[idPieza].pos.x - 1 && (y == listPiecePos[idPieza].pos.y + 2 || y == listPiecePos[idPieza].pos.y - 2)))
				{
					movimientoValido = true;
				}
				else
				{
					movimientoValido = false;
				}
			}
			else if (listPiecePos[idPieza].piece == BLACK_KING || listPiecePos[idPieza].piece == WHITE_KING)
			{
				if ((((x == listPiecePos[idPieza].pos.x || x == listPiecePos[idPieza].pos.x - 1 || x == listPiecePos[idPieza].pos.x + 1) && (y == listPiecePos[idPieza].pos.y || y == listPiecePos[idPieza].pos.y - 1 || y == listPiecePos[idPieza].pos.y + 1)) && !(x == listPiecePos[idPieza].pos.x && y == listPiecePos[idPieza].pos.y) && !casillaAtacada(x, y)) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
				{
					movimientoValido = true;
				}
				else
				{
					movimientoValido = false;
				}
			}
			else if (listPiecePos[idPieza].piece == BLACK_QUEEN || listPiecePos[idPieza].piece == WHITE_QUEEN)
			{
				if ((((x - listPiecePos[idPieza].pos.x) + (y - listPiecePos[idPieza].pos.y) == 0 || (x - listPiecePos[idPieza].pos.x) - (y - listPiecePos[idPieza].pos.y) == 0) || ((x == listPiecePos[idPieza].pos.x && (y > listPiecePos[idPieza].pos.y || y < listPiecePos[idPieza].pos.y)) || (y == listPiecePos[idPieza].pos.y && (x < listPiecePos[idPieza].pos.x || x > listPiecePos[idPieza].pos.x)))) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
				{
					movimientoValido = true;
				}
				else
				{
					movimientoValido = false;
				}
			}
		}

		if (!movimientoValido)
		{
			break;
		}

	} while (!movimientoValido);

}