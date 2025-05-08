#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "comprobaciones.h"

void generarMovimientosPeon(Pieces& peon, int jugador, std::vector<Position>& movimientosPosibles) {
	
	int direccion = (jugador == JUGADOR1) ? -1 : 1;

	movimientosPosibles.push_back({ peon.pos.x + direccion, peon.pos.y });

	if ((jugador == JUGADOR1 && peon.pos.x == 6) || (jugador == JUGADOR2 && peon.pos.x == 1))
	{
		movimientosPosibles.push_back({ peon.pos.x + 2 * direccion, peon.pos.y });
	}

	movimientosPosibles.push_back({ peon.pos.x + direccion, peon.pos.y + 1 });
	movimientosPosibles.push_back({ peon.pos.x + direccion, peon.pos.y - 1 });
}

void generarMovimientosTorre(Pieces& torre, int jugador, std::vector<Position>& movimientosPosibles) {
	
	for (int i = 0; i < BOARD_SIZE; ++i) {

		if (i != torre.pos.y) {
			movimientosPosibles.push_back({ torre.pos.x, i });
		}

		if (i != torre.pos.x) {
			movimientosPosibles.push_back({ i, torre.pos.y });
		}
	}
}

void generarMovimientosCaballo(Pieces& caballo, int jugador, std::vector<Position>& movimientosPosibles) {
	
	std::vector<Position> movimientos = { {2, 1},{2, -1},{-2, 1},{-2, -1},{1, 2},{1, -2},{-1, 2},{-1, -2} };

	for (int i = 0; i < movimientos.size(); i++)
	{
		Position destino = { caballo.pos.x + movimientos[i].x, caballo.pos.y + movimientos[i].y };

		if (destino.x >= 0 && destino.x < BOARD_SIZE && destino.y >= 0 && destino.y < BOARD_SIZE)
		{
			movimientosPosibles.push_back(destino);
		}
	}
}

void generarMovimientosAlfil(Pieces& alfil, int jugador, std::vector<Position>& movimientosPosibles) {
	
	for (int i = 1; i < BOARD_SIZE; ++i) {
		
		if (alfil.pos.x + i < BOARD_SIZE && alfil.pos.y + i < BOARD_SIZE)
			movimientosPosibles.push_back({ alfil.pos.x + i, alfil.pos.y + i });

		if (alfil.pos.x + i < BOARD_SIZE && alfil.pos.y - i >= 0)
			movimientosPosibles.push_back({ alfil.pos.x + i, alfil.pos.y - i });

		if (alfil.pos.x - i >= 0 && alfil.pos.y + i < BOARD_SIZE)
			movimientosPosibles.push_back({ alfil.pos.x - i, alfil.pos.y + i });

		if (alfil.pos.x - i >= 0 && alfil.pos.y - i >= 0)
			movimientosPosibles.push_back({ alfil.pos.x - i, alfil.pos.y - i });
	}
}

void generarMovimientosReina(Pieces& reina, int jugador, std::vector<Position>& movimientosPosibles){
	
	generarMovimientosTorre(reina, jugador, movimientosPosibles);
	generarMovimientosAlfil(reina, jugador, movimientosPosibles);

}

void generarMovimientosRey(Pieces& rey, int jugador, std::vector<Position>& movimientosPosibles) {
	
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (dx == 0 && dy == 0)
			{
				continue;
			}

			Position destino = { rey.pos.x + dx, rey.pos.y + dy };

			if (destino.x >= 0 && destino.x < BOARD_SIZE && destino.y >= 0 && destino.y < BOARD_SIZE)
			{
				movimientosPosibles.push_back(destino);
			}
		}
	}
}

void movimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& movimientoValido, Position& casillaFinal, bool& comer, bool& enroque, int& contador50Movimientos) {

	validarMovimiento(listPiecePos, idPieza, jugador, comer, movimientoValido, casillaFinal, enroque, contador50Movimientos);

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

bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador, int& contador50Movimientos, std::vector<std::string>& historialPosiciones) {

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
		movimiento(listPiecePos, idPieza, jugador, movimientoValido, casillaFinal, comer, enroque, contador50Movimientos);

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

			Position casillaInicial = listPiecePos[idPieza].pos;


			cambiarPosicion(idPieza, casillaFinal, listPiecePos, enroque);

			if (jaque(listPiecePos, jugador))
			{
				cambiarPosicion(idPieza, casillaInicial, listPiecePos, enroque);
				std::cout << "Tu rey no puede estar en Jaque!" << std::endl;
				Sleep(1500);
				goto choosePiece;
			}

			listPiecePos[idPieza].moved = true;


			
		}
		return true;
	}
	else
	{
		return false;
	}
}