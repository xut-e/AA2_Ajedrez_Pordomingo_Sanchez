#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "moves.h"
#include "comprobaciones.h"

//Funcion para actualizar el tablero, colocamos las piezas que no han sido capturadas
void updateChessboard(std::vector<Pieces> listPiecePos, char chessboard[BOARD_SIZE][BOARD_SIZE]) {
	
	initChessBoard(chessboard);

	for (int i = 0; i < TOTAL_PIECES; i++)
	{
		if (listPiecePos[i].active)
		{
			chessboard[listPiecePos[i].pos.x][listPiecePos[i].pos.y] = listPiecePos[i].piece;
		}
	}

}

//Funcion principal del juego
void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos) {
	
	bool checkmate = false, rendicion = false, hayTablas = false;
	int ganador, idPieza, contador50Movimientos = 0;
	char opcionElegida, opcionRendicion, opcionTablas;
	
	while (true)
	{
		//For para los turnos mientras no haya jaque mate o rendicion o tablas
		for (int i = 0; i < JUGADORES; i++)
		{
			do
			{
			start:

				system("cls");
				updateChessboard(listPiecesPos, chessboard);
				viewChessBoard(chessboard);

				if (jaque(listPiecesPos, i))
				{
					std::cout << "Jaque!" << std::endl;
				}

				//Menu que permite al jugador escoger que hacer en su turno
				std::cout << "Turno de " << ((i == JUGADOR1) ? "blancas." : "negras.") << std::endl;

				std::cout << "\t 1. Mover. \n \t 2. Rendirse. \n \t 3. Ofrecer tablas. \n Elige una opcion: ";
				std::cin >> opcionElegida;

				if (opcionElegida == '1')
				{
					if (movePiece(chessboard, listPiecesPos, i, contador50Movimientos))
					{
						if (coronacion(listPiecesPos, i, idPieza))
						{
							char opcionCoronacion;

							if (i == 0)
							{
								std::cout << std::endl << "\tB) Alfil.\n\tH) Caballo\n\tT) Torre\n\tQ) Dama\n\n" << "Has coronado un peon, elige en que pieza transformarlo:";

								do
								{
									std::cin >> opcionCoronacion;

									if (opcionCoronacion != 'B' && opcionCoronacion != 'H' && opcionCoronacion != 'T' && opcionCoronacion != 'Q')
									{
										std::cout << "Selecciona una opcion valida:" << std::endl;
									}
								} while (opcionCoronacion != 'B' && opcionCoronacion != 'H' && opcionCoronacion != 'T' && opcionCoronacion != 'Q');
							}
							else
							{
								std::cout << std::endl << "\tb) Alfil.\n\th) Caballo\n\tt) Torre\n\tq) Dama\n\n" << "Has coronado un peon, elige en que pieza transformarlo:";

								do
								{
									std::cin >> opcionCoronacion;

									if (opcionCoronacion != 'b' && opcionCoronacion != 'h' && opcionCoronacion != 't' && opcionCoronacion != 'q')
									{
										std::cout << "Selecciona una opcion valida:" << std::endl;
									}
								} while (opcionCoronacion != 'b' && opcionCoronacion != 'h' && opcionCoronacion != 't' && opcionCoronacion != 'q');
							}

							cambiarPieza(listPiecesPos, idPieza, opcionCoronacion);
						}
					}
					else
					{
						goto start;
					}

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
					else
					{
						goto start;
					}
				}
				else if (opcionElegida == '3')
				{
					system("cls");
					std::cout << "Jugador con " << ((i == JUGADOR1) ? "negras" : "blancas") << ", tu rival te ha enviado una oferta de tablas. \n \t 1. Aceptar tablas. \n \t 2. Rechazar tablas \n Aceptas?: ";
					std::cin >> opcionTablas;

					if (opcionTablas == '1')
					{
						hayTablas = true;
					}
					else
					{
						goto start;
					}
				}
				else
				{
					system("cls");
					std::cout << "Opcion invalida!";
					Sleep(1500);
					goto start;
				}

				if (checkmate || rendicion || hayTablas)
				{
					break;
				}

			} while (opcionElegida != '1' && movePiece(chessboard, listPiecesPos, i, contador50Movimientos));

			

			if (rendicion)
			{
				(i == JUGADOR1) ? ganador = JUGADOR2 : ganador = JUGADOR1;
				break;
			}

			if (hayTablas)
			{
				ganador = TABLAS;
				break;
			}

			if (jaque(listPiecesPos, i))
			{
				if (jaqueMate(listPiecesPos, i))
				{
					checkmate = true;
					ganador = i;
					break;					
				}
			}

			if (tablas(listPiecesPos, i, contador50Movimientos))
			{
				hayTablas = true;
				ganador = TABLAS;
				break;
			}
		}

		if (checkmate || rendicion || hayTablas)
		{
			break;
		}
	}

	//Finalizacion de la partida, especificamos si hay ganador quien es y si no lo hay declaramos empate
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