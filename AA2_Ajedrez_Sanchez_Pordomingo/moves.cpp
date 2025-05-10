#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "comprobaciones.h"

//Funciones que generan movimientos para la simulación de estos (imprescindible para el jaque mate)
//Generar movimientos posibles de peones
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

//Generar movimientos posibles de torres
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

//Generar movimientos posibles de caballos
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

//Generar movimientos posibles de alfiles
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

//Generar movimientos posibles de reinas
void generarMovimientosReina(Pieces& reina, int jugador, std::vector<Position>& movimientosPosibles){
	
	generarMovimientosTorre(reina, jugador, movimientosPosibles);
	generarMovimientosAlfil(reina, jugador, movimientosPosibles);

}

//Generar movimientos posibles de reyes
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

//Validamos el movimiento del usuario (el que él ha introducido) para ver si se puede ejecutar. Si hubiera hecho antes la generación de movimientos pensando en el jaque mate primero podría haberme ahorrado esta función (validarMovimiento()).
void movimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& movimientoValido, Position& casillaFinal, bool& comer, bool& enroque, int& contador50Movimientos) {

	validarMovimiento(listPiecePos, idPieza, jugador, comer, movimientoValido, casillaFinal, enroque, contador50Movimientos);

}

//Funcion para cambiar la pieza en la coronación.
void cambiarPieza(std::vector<Pieces>& listPiecePos, int idPieza, char piezaElegida) {
	
	listPiecePos[idPieza].piece = piezaElegida;
}

//Función para cambiar la posición de una pieza cuando se mueve. Sirve también para el enroque.
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

//Menú que sale al escoger mover una pieza
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

//Funcion para asegurar que la pieza escogida te pertenece, que en la casilla hay una pieza y para comprobar que puedes moverla a donde quieres y hacerlo.
bool movePiece(char chessboard[BOARD_SIZE][BOARD_SIZE], std::vector<Pieces>& listPiecePos, int jugador, int& contador50Movimientos, std::vector<std::string>& historialPosiciones) {

	int minimoRango, maximoRango, opcionElegida, x, y, idPieza, idPiezaComida;

	bool movimientoValido = false, comer = false, enroque = false;

	Position casillaFinal;

	//Etiqueta que facilita el flujo del programa
choosePiece:

	system("cls");
	viewChessBoard(chessboard);

	//Declaramos el rango de las piezas del jugador, podría haber usado una estructura Position la verdad
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

	//Le pedimos una pieza para mover hasta que introduzca una válida
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

		//Si el movimiento no es válido lo mandamos a escoger una pieza otra vez
		if (!movimientoValido)
		{
			std::cout << "No puedes mover ahi!" << std::endl;
			Sleep(ESPERA);
			goto choosePiece;
		}
		//Si es válido comprobamos si come o no
		else
		{
			//Si come cambiamos el estado de la pieza comida a active = false 
			if (comer)
			{
				for (size_t i = 0; i < listPiecePos.size(); i++)
				{
					if (casillaFinal.x == listPiecePos[i].pos.x && casillaFinal.y == listPiecePos[i].pos.y)
					{
						listPiecePos[i].active = false;
						idPiezaComida = i;
						break;
					}
				}
			}

			Position casillaInicial = listPiecePos[idPieza].pos;

			//Cambiamos la posicion de la pieza movida
			cambiarPosicion(idPieza, casillaFinal, listPiecePos, enroque);

			//Si al terminar la jugada el rey está en jaque advertimos de que no es un movimiento válido y devolvemos la pieza a su casilla inicial y si habíamos comido alguna la devolvemos a su estado original y volvemos a escogher pieza.
			if (jaque(listPiecePos, jugador))
			{
				if (comer)
				{
					listPiecePos[idPiezaComida].active = true;
				}
				cambiarPosicion(idPieza, casillaInicial, listPiecePos, enroque);
				std::cout << "Tu rey no puede estar en Jaque!" << std::endl;
				Sleep(ESPERA);
				goto choosePiece;
			}

			//Si nada de eso pasa y el movimiento es válido cambiamos el estado de la pieza movida a moved = true.
			listPiecePos[idPieza].moved = true;


			
		}

		//Si hemos acabado moviendo la pieza devolvemos true
		return true;
	}
	//Si no, devolvemos false
	else
	{
		return false;
	}
}