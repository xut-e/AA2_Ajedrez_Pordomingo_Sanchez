#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "moves.h"
#include "comprobaciones.h"
#include <string>

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

//Funcion para obtener una clave �nica de tablero, nos sirve para compararlas y saber si hay tablas por repetici�n de tres movimientos, tambi�n pood�a haber usado la notaci�n fen (que es la que usa la API REST de Stockfish), pero prefer� hacer una yo mismo.
std::string obtenerClaveTablero(std::vector<Pieces>& listPiecePos, int jugador) {

	std::string clave;

	for (int i = 0; i < listPiecePos.size(); i++)
	{
		if (listPiecePos[i].active)
		{
			clave += (jugador == JUGADOR1) ? "W" : "B";
			clave += listPiecePos[i].piece;
			clave += std::to_string(listPiecePos[i].pos.x);
			clave += std::to_string(listPiecePos[i].pos.y);
		}
	}

	return clave;
}

//Funcion principal del juego
void play(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecesPos) {
	
	//Variables varias
	bool checkmate = false, rendicion = false, hayTablas = false;
	int ganador, idPieza, contador50Movimientos = 0, tipoTablas = 0;
	char opcionElegida, opcionRendicion, opcionTablas;

	std::vector<std::string> historialPosiciones;
	
	//Bucle que se repite hasta que haya jaque mate (break;). Lo hago as� porque jaque mate depende del jugador que est� en su turno, por lo que no puedo llamar a la funci�n jaquemate fuera del bucle for que maneja los turnos.
	while (true)
	{
		//For para los turnos mientras no haya jaque mate o rendicion o tablas
		for (int i = 0; i < JUGADORES; i++)
		{
			
			std::string posicionActual = obtenerClaveTablero(listPiecesPos, i);

			//Al principio del turno comprobamos si hay jaque mate
			if (jaqueMate(listPiecesPos, i)) {
				checkmate = true;
				ganador = (i + 1) % JUGADORES; // The other player wins
				
				//Si lo hay actualizamos el tablero para que se vea la jugada que ha causado el jaque mate
				system("cls");
				updateChessboard(listPiecesPos, chessboard);
				viewChessBoard(chessboard);

				break;
			}

			//Antes de hacer cualquier movimiento guardamos la posici�n del tablero en el historial
			historialPosiciones.push_back(posicionActual);

			//Con este dowhile nos aseguramos de que continue mostrando el men� mientras el jugador no elija la opci�n 1 (mover) y mueva, ya que al elegir cualquier otra opci�n si la partida se tiene que acabar haremos break.
			do
			{
				//Esta etiqueta nos ayuda a manejar mejor el flujo del programa
			start:

				system("cls");
				updateChessboard(listPiecesPos, chessboard);
				viewChessBoard(chessboard);

				//Si el movimiento anterior desencaden� en jaque se lo decimos al usuario
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
					//Lamamos a la funci�n que obtiene el movimiento (solo devolver� true si acabamos moviento una pieza)
					if (movePiece(chessboard, listPiecesPos, i, contador50Movimientos, historialPosiciones))
					{
						//Si el jugador ha coronado despu�s de mover le sale el siguiente men� donde puede elegir en qu� pieza convertir su pe�n coronado
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

							//Despu�s de elegir la pieza que quiere la cambiamos por el pe�n
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
					//Men� de rendici�n
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
					//Mensaje de tablas
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
				//Si elegimos una opci�n que no aparece en el men� de opciones
				else
				{
					system("cls");
					std::cout << "Opcion invalida!";
					Sleep(ESPERA);
					goto start;
				}

				//Si al final del turno hay cualquiera de estas salimos del bucle dowhile
				if (checkmate || rendicion || hayTablas)
				{
					break;
				}

			} while (opcionElegida != '1' && movePiece(chessboard, listPiecesPos, i, contador50Movimientos, historialPosiciones));

			
			//Si alguien se ha rendido establecemos el ganador y salimos
			if (rendicion)
			{
				(i == JUGADOR1) ? ganador = JUGADOR2 : ganador = JUGADOR1;
				break;
			}

			//Si hay tablas establecemos tablas como ganador, establecemos la�raz�n de las tablas y salimos
			if (tablas(listPiecesPos, i, contador50Movimientos, historialPosiciones, tipoTablas))
			{
				hayTablas = true;
				ganador = TABLAS;
				break;
			}
		}

		//Si hay cualquiera de las tres salimos del bucle principal
		if (checkmate || rendicion || hayTablas)
		{
			break;
		}
	}

	//Finalizacion de la partida
	//Si el jugador ganador es blancas damos la raz�n y lo decimos
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
	//Si el jugador ganador es negras damos la raz�n y lo decimos
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
	//Si el jugador ganador es tablas damos la raz�n y declaramos el empate
	else if (ganador == TABLAS)
	{
		std::cout << "La partida ha quedado en tablas (empate). Causa:\n" << std::endl;
		
		if (tipoTablas == 1)
		{
			std::cout << "Rey ahogado." << std::endl;
		}
		else if (tipoTablas == 2)
		{
			std::cout << "Falta de material." << std::endl;
		}
		else if (tipoTablas == 3)
		{
			std::cout << "Repetici�n del tablero tres veces." << std::endl;
		}
		else if (tipoTablas == 4)
		{
			std::cout << "Cincuenta movimientos sin capturas ni movimiento de peones." << std::endl;
		}
	}
}