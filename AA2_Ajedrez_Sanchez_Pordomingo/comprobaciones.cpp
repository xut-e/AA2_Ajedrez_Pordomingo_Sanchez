#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"

bool piezaEnMedio(Position casillaInicial, Position casillaFinal, char pieza,std::vector<Pieces> listPiecePos, bool comer, bool salidaMaxima) {

	if (pieza == WHITE_ROOK || pieza == BLACK_ROOK || pieza == WHITE_QUEEN || pieza == BLACK_QUEEN || ((pieza == WHITE_PAWN || pieza == BLACK_PAWN) && !comer && salidaMaxima))
	{
		// Movimiento vertical (misma columna)
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
		// Movimiento horizontal (misma fila)
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
		//Para que el movimiento sea valido, incrementoX = incrementoY (movimiento diagonal)
		int incrementoX = ((casillaFinal.x - casillaInicial.x) < 0) ? (casillaFinal.x - casillaInicial.x) * (-1) : (casillaFinal.x - casillaInicial.x);
		int incrementoY = ((casillaFinal.y - casillaInicial.y) < 0) ? (casillaFinal.y - casillaInicial.y) * (-1) : (casillaFinal.y - casillaInicial.y);

		if (incrementoX == incrementoY && incrementoX > 0)
		{
			int stepX = (casillaFinal.x > casillaInicial.x) ? 1 : -1, stepY = (casillaFinal.y > casillaInicial.y) ? 1 : -1;

			for (int i = 0; i < incrementoX; i++)
			{
				for ( size_t j = 0; j < listPiecePos.size(); j++)
				{
					if (listPiecePos[j].active && listPiecePos[j].pos.x == casillaInicial.x + (i * stepX) && listPiecePos[j].pos.y == casillaInicial.y + (i * stepY))
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

void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido) {
	
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
		

		Position casillaFinal = { x,y };

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
			
		}
		else
		{
			if ((listPiecePos[idPieza].piece == WHITE_PAWN || listPiecePos[idPieza].piece == BLACK_PAWN) && !listPiecePos[idPieza].moved)
			{
				salidaMaxima = true;
			}

			if (listPiecePos[idPieza].piece == BLACK_PAWN)
			{
				if (comer)
				{
					if ((x == listPiecePos[idPieza].pos.x + 1 && (y == listPiecePos[idPieza].pos.y - 1 || y == listPiecePos[idPieza].pos.y + 1)))
					{
						movimientoValido = true;
					}
				}
				else
				{
					if (salidaMaxima && !comer)
					{
						if (x == listPiecePos[idPieza].pos.x + 2 && y == listPiecePos[idPieza].pos.y && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
						{
							movimientoValido = true;
						}
					}

					if ((x == listPiecePos[idPieza].pos.x + 1 && y == listPiecePos[idPieza].pos.y) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
					{
						movimientoValido = true;
					}
					else if ((listPiecePos[idPieza].pos.x == 1) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
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
				else
				{
					if (salidaMaxima && !comer)
					{
						if (x == listPiecePos[idPieza].pos.x - 2 && y == listPiecePos[idPieza].pos.y && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
						{
							movimientoValido = true;
						}
					}

					if (((x == listPiecePos[idPieza].pos.x - 1 && y == listPiecePos[idPieza].pos.y)) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
					{
						movimientoValido = true;
					}
					else if ((listPiecePos[idPieza].pos.x == 6) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
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
			else if (listPiecePos[idPieza].piece == BLACK_BISHOP || listPiecePos[idPieza].piece == WHITE_BISHOP)
			{
				if (((x - listPiecePos[idPieza].pos.x) + (y - listPiecePos[idPieza].pos.y) == 0 || (x - listPiecePos[idPieza].pos.x) - (y - listPiecePos[idPieza].pos.y) == 0) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
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