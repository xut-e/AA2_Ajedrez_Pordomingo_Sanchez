#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "comprobaciones.h"

void movimiento(std::vector<Pieces>& listPiecePos, int idPieza) {

	if (listPiecePos[idPieza].piece == BLACK_PAWN || listPiecePos[idPieza].piece == WHITE_PAWN)
	{

	}
	else if (listPiecePos[idPieza].piece == BLACK_ROOK || listPiecePos[idPieza].piece == WHITE_ROOK)
	{

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
		return false;
	}
	if (opcion == '2')
	{
		return true;
	}

	return false;
}

bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador) {

	int minimoRango, maximoRango, opcionElegida, x, y, idPieza;

	if (jugador == JUGADOR1)
	{
		minimoRango = 16;
		maximoRango = 31;
	}
	else
	{
		minimoRango = 0;
		maximoRango = 15;
	}

	do
	{
		std::cout << "Selecciona una pieza para mover (fila y columna): ";
		std::cin >> x >> y;

		x = 8 - x;
		y -= 1;

	} while (!playerOwnsPiece(x, y, listPiecePos, jugador, idPieza));

	//Si la pieza le pertenece comienza la logica de movimiento

	//Movimiento

	menuMovimiento();

	if (menuMovimiento())
	{
		return false;
	}
	else
	{
		movimiento(listPiecePos, idPieza);
		return true;
	}
}