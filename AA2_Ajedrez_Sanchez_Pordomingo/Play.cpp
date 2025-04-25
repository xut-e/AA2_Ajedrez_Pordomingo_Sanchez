#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"

bool comprobarJaqueMate(std::vector<Pieces>& listPiecesPos, int jugador) {
	return false;
}

bool comprobarJaque(std::vector<Pieces>& listPiecesPos, int jugador) {
	return false;
}

void updateChessboard(std::vector<Pieces> listPiecePos, char chessboard[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < TOTAL_PIECES; i++)
	{
		chessboard[listPiecePos[i].pos.x][listPiecePos[i].pos.y] = listPiecePos[i].piece;
	}

}

void movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador) {

}

bool comprobarTablas(std::vector<Pieces> listPiecesPos, int jugador) {
	return false;
}

void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos) {
	
	bool checkmate = false, rendicion = false, tablas = false;
	int ganador;
	char opcionElegida, opcionRendicion, opcionTablas;
	
	while (true)
	{
		for (int i = 0; i < JUGADORES; i++)
		{
			
			//Menú:
				//1. Mover
				//2. Rendirse
				//3. Ofrecer tablas

			//Logica de movimientos

			do
			{
				system("cls");
				viewChessBoard(chessboard);

				std::cout << "Turno de " << ((i == JUGADOR1) ? "blancas." : "negras.") << std::endl;

				std::cout << "\t 1. Mover. \n \t 2. Rendirse. \n \t 3. Ofrecer tablas. \n Elige una opcion: ";
				std::cin >> opcionElegida;

				if (opcionElegida == '1')
				{
					movePiece(chessboard, listPiecesPos, i);
				}
				else if (opcionElegida == '2')
				{
					std::cout << "Rendicion. \n \t 1. Rendirme. \n \t 2. Volver atras. \n Vas a rendirte. Estas seguro?: ";
					std::cin >> opcionRendicion;

					if (opcionRendicion == '1')
					{
						rendicion = true;
						break;
					}
				}
				else if (opcionElegida == '3')
				{
					system("cls");
					std::cout << "Jugador con " << ((i == JUGADOR1) ? "negras" : "blancas") << ", tu rival te ha enviado una oferta de tablas. \n \t 1. Aceptar tablas. \n \t 2. Rechazar tablas \n Aceptas?: ";
					std::cin >> opcionTablas;

					if (opcionTablas == '1')
					{
						tablas = true;
					}
				}
				else
				{
					system("cls");
					std::cout << "Opcion invalida!";
					Sleep(1500);
				}

			} while (opcionElegida != '1');

			if (rendicion)
			{
				(i == JUGADOR1) ? ganador = JUGADOR2 : ganador = JUGADOR1;
				break;
			}

			if (tablas)
			{
				ganador = TABLAS;
				break;
			}

			if (comprobarJaque(listPiecesPos, i))
			{
				if (comprobarJaqueMate(listPiecesPos, i))
				{
					checkmate = true;
					ganador = i;
					break;					
				}
			}

			if (comprobarTablas(listPiecesPos, i))
			{
				tablas = true;
				ganador = TABLAS;
				break;
			}
		}

		if (checkmate)
		{
			break;
		}
	}

	if (ganador == JUGADOR1)
	{
		if (rendicion)
		{
			std::cout << "Las blancas ganan por rendicion de las negras." << std::endl;
		}
		else
		{
			std::cout << "Las blancas ganan por jaque mate." << std::endl;
		}
		
	}
	else if (ganador == JUGADOR2)
	{
		if (rendicion)
		{
			std::cout << "Las negras ganan por rendicion de las blancas." << std::endl;
		}
		else
		{
			std::cout << "Las negras ganan por jaque mate." << std::endl;
		}
	}
	else if (ganador == TABLAS)
	{
		std::cout << "La partida ha quedado en tablas (empate)." << std::endl;
	}
}

