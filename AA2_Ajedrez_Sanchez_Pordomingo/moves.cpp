#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "comprobaciones.h"

void movimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& movimientoValido, Position& casillaFinal, bool& comer, bool& enroque) {

	validarMovimiento(listPiecePos, idPieza, jugador, comer, movimientoValido, casillaFinal, enroque);

}

void cambiarPieza(std::vector<Pieces>& listPiecePos, int idPieza, char piezaElegida) {
	
	listPiecePos[idPieza].piece = piezaElegida;
}

void cambiarPosicion(int idPieza, Position casillaFinal, std::vector<Pieces>& listPiecePos, bool& enroque) {
	int torre;
	
	if (enroque)
	{
		if (idPieza >= 16 && casillaFinal.y < listPiecePos[idPieza].pos.y)
		{
			torre = 16;
		}
		else if (idPieza >= 16 && casillaFinal.y > listPiecePos[idPieza].pos.y)
		{
			torre = 23;
		}
		else if (idPieza < 16 && casillaFinal.y < listPiecePos[idPieza].pos.y)
		{
			torre = 0;
		}
		else
		{
			torre = 7;
		}



		if (torre == 16 || torre == 0)
		{
			listPiecePos[torre].pos.y = casillaFinal.y + 1;
		}
		else if (torre == 23 || torre == 7)
		{
			listPiecePos[torre].pos.y = casillaFinal.y - 1;
		}
	}


	listPiecePos[idPieza].pos.x = casillaFinal.x;
	listPiecePos[idPieza].pos.y = casillaFinal.y;
}

bool menuMovimiento() {
	char opcion;

	std::cout << "\n \t1. Escoger casilla para mover.\n \t2. Volver atras.\nEscoge una opcion: ";

	do
	{
		std::cin >> opcion;

		if (opcion != '1' && opcion != '2')
		{
			std::cout << "Esa opcion no es válida!" << std::endl;
		}
	} while (opcion != '1' && opcion != '2');

	if (opcion == '1')
	{
		return true;
	}
	else if (opcion == '2')
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador) {

	int minimoRango, maximoRango, opcionElegida, x, y, idPieza;

	bool movimientoValido = false, comer = false, enroque = false;

	Position casillaFinal;

choosePiece:

	system("cls");
	viewChessBoard(chessboard);

	if (jugador == JUGADOR1)
	{
		minimoRango = 16;
		maximoRango = 31;

		idPieza = 15;
	}
	else
	{
		minimoRango = 0;
		maximoRango = 15;

		idPieza = 16;
	}

	do
	{
		std::cout << "Selecciona una pieza para mover (fila y columna): ";
		std::cin >> x >> y;

		x = 8 - x;
		y -= 1;

		for (int i = 0; i < listPiecePos.size(); i++)
		{
			if (x == listPiecePos[i].pos.x && y == listPiecePos[i].pos.y)
			{
				idPieza = i;
				break;
			}
		}

	} while (!playerOwnsPiece(x, y, listPiecePos, jugador, idPieza) && listPiecePos[idPieza].active);

	//Si la pieza le pertenece comienza la logica de movimiento

	//Movimiento

	
	if (menuMovimiento())
	{
		movimiento(listPiecePos, idPieza, jugador, movimientoValido, casillaFinal, comer, enroque);

		if (!movimientoValido)
		{
			std::cout << "No puedes mover ahi!" << std::endl;
			Sleep(1500);
			goto choosePiece;
		}
		else
		{
			if (comer)
			{
				for (size_t i = 0; i < listPiecePos.size(); i++)
				{
					if (casillaFinal.x == listPiecePos[i].pos.x && casillaFinal.y == listPiecePos[i].pos.y)
					{
						listPiecePos[i].active = false;
						break;
					}
				}
			}
			cambiarPosicion(idPieza, casillaFinal, listPiecePos, enroque);
			listPiecePos[idPieza].moved = true;
			
		}
		return true;
	}
	else
	{
		return false;
	}
}