#include "Library.h"
#include "utils.h"
#include "Const.h"
#include "init.h"
#include "Play.h"
#include "moves.h"
#include "comprobaciones.h"

//Buscamos la posicion del rey
int encontrarRey(const std::vector<Pieces>& listPiecesPos, int jugador) {
	char reyBuscado = (jugador == JUGADOR1) ? WHITE_KING : BLACK_KING;

	for (int i = 0; i < listPiecesPos.size(); ++i) 
	{
		if (listPiecesPos[i].active && listPiecesPos[i].piece == reyBuscado) {
			return i; //Devolvemos el id del rey
		}
	}
	return -1; // Nunca debería ocurrir
}

//Validamos los movimientos que hemos generado con las funciones de generar movimientos
void validarMovimientoSimulado(std::vector<Pieces>& copiaPiezas, int idPieza, Position destino, int jugador, bool& movimientoValido, bool& comer, bool& enroque) {
	Position posicionOriginal = copiaPiezas[idPieza].pos;
	bool estadoOriginalActive = copiaPiezas[idPieza].active;
	char tipoPieza = toupper(copiaPiezas[idPieza].piece);

	movimientoValido = false;
	comer = false;
	enroque = false;

	//Validamos movimiento segun tipo de pieza (ayuda de la IA)
	if (tipoPieza == 'P') 
	{
		bool movimientoDoble = (abs(posicionOriginal.x - destino.x) == 2);

		if (piezaEnMedio(posicionOriginal, destino, copiaPiezas[idPieza].piece, copiaPiezas, false, movimientoDoble)) 
		{
			return; //Si el peon avanza dos casillas y hay una pieza en medio invalidamos el movimiento
		}

		// Movimiento hacia adelante
		if (destino.y == posicionOriginal.y) 
		{
			
			for (int i = 0; i < copiaPiezas.size(); i++) 
			{
				if (copiaPiezas[i].active && copiaPiezas[i].pos.x == destino.x && copiaPiezas[i].pos.y == destino.y) {
					return; // Casilla ocupada
				}
			}
		}
		// Captura diagonal
		else 
		{
			bool capturaValida = false;

			for (int i = 0; i < copiaPiezas.size(); i++) 
			{
				if (copiaPiezas[i].active && copiaPiezas[i].pos.x == destino.x && copiaPiezas[i].pos.y == destino.y) 
				{
					if ((jugador == JUGADOR1 && !isupper(copiaPiezas[i].piece)) || (jugador == JUGADOR2 && isupper(copiaPiezas[i].piece))) 
					{
						comer = true;
						capturaValida = true;
						copiaPiezas[i].active = false;
						break;
					}
				}
			}

			if (!capturaValida)
			{
				return;
			}
		}
	}
	else if (tipoPieza == 'T' || tipoPieza == 'B' || tipoPieza == 'Q' || tipoPieza == 'H' || tipoPieza == 'K') 
	{
		if (tipoPieza != 'H' && piezaEnMedio(posicionOriginal, destino, copiaPiezas[idPieza].piece, copiaPiezas, false, false)) 
		{
			return;
		}

		// Verificar captura
		for (int i = 0; i < copiaPiezas.size(); i++) 
		{
			if (copiaPiezas[i].active && copiaPiezas[i].pos.x == destino.x && copiaPiezas[i].pos.y == destino.y) 
			{
				if ((jugador == JUGADOR1 && !isupper(copiaPiezas[i].piece)) || (jugador == JUGADOR2 && isupper(copiaPiezas[i].piece))) 
				{
					comer = true;
					copiaPiezas[i].active = false;
				}
				else 
				{
					return; // Pieza aliada en el destino
				}
				break;
			}
		}
	}

	// Mover la pieza temporalmente
	copiaPiezas[idPieza].pos = destino;

	// Verificar si el movimiento deja al rey en jaque
	if (!jaque(copiaPiezas, jugador)) 
	{
		movimientoValido = true;
	}

	// Restaurar estado original
	copiaPiezas[idPieza].pos = posicionOriginal;
	copiaPiezas[idPieza].active = estadoOriginalActive;

	//Si se ha comido en la simulacion retornamos el estado original
	if (comer) 
	{
		for (int i = 0; i < copiaPiezas.size(); i++) 
		{
			if (!copiaPiezas[i].active && copiaPiezas[i].pos.x == destino.x && copiaPiezas[i].pos.y == destino.y) 
			{
				copiaPiezas[i].active = true;
				break;
			}
		}
	}
}

//Funcion para comprobar que no hay piezas entre la casilla inicial y la final (los caballos nunca llaman a esta función)
bool piezaEnMedio(Position casillaInicial, Position casillaFinal, char pieza,std::vector<Pieces> listPiecePos, bool comer, bool salidaMaxima) {

	//Horizontal o vertical
	if (pieza == WHITE_ROOK || pieza == BLACK_ROOK || pieza == WHITE_QUEEN || pieza == BLACK_QUEEN || ((pieza == WHITE_PAWN || pieza == BLACK_PAWN) && !comer && salidaMaxima) || (pieza == BLACK_KING || pieza == WHITE_KING))
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

	//Diagonal (ayuda de la IA)
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

bool casillaAtacada(Position& casillaAComprobar, int jugadorAtacante, std::vector<Pieces> listPiecePos)
{
	//Aquí sí que use una variable Position, era un momento más avanzado del desarrollo
	Position rango;

	if (jugadorAtacante == JUGADOR1) {
		rango.x = (TOTAL_PIECES / 2);
		rango.y = (TOTAL_PIECES - 1);
	}
	else {
		rango.x = 0;
		rango.y = ((TOTAL_PIECES / 2) - 1);
	}

	for (int i = rango.x; i <= rango.y; i++) {
		if (listPiecePos[i].active) {
			Position posPieza = listPiecePos[i].pos;
			char tipoPieza = listPiecePos[i].piece;

			if (puedeAtacar(posPieza, tipoPieza, casillaAComprobar, listPiecePos)) {
				return true;
			}
		}
	}

	return false;
}

//Función para verificar si hay coronación al acabar el movimiento
bool coronacion(std::vector<Pieces>& listPiecePos, int jugador, int& idPieza) {
	
	
	if (jugador == JUGADOR1)
	{
		for (int i = (TOTAL_PIECES / 2); i < TOTAL_PIECES; i++)
		{
			if (listPiecePos[i].piece == WHITE_PAWN && listPiecePos[i].active && listPiecePos[i].pos.x == 0)
			{
				idPieza = i;
				return true;
			}
		}
	}
	else
	{
		if (jugador == JUGADOR2)
		{
			for (int i = 0; i < (TOTAL_PIECES / 2); i++)
			{
				if (listPiecePos[i].piece == BLACK_PAWN && listPiecePos[i].active && listPiecePos[i].pos.x == 7)
				{
					idPieza = i;
					return true;
				}
			}
		}
	}
	
	
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
				if (!(i >= (TOTAL_PIECES / 2) && i < TOTAL_PIECES))
				{
					std::cout << "Esa pieza no es tuya!" << std::endl;
				}
				return (i >= (TOTAL_PIECES / 2) && i < TOTAL_PIECES);
			}
			else
			{
				if (!(i >= 0 && i < (TOTAL_PIECES / 2)))
				{
					std::cout << "Esa pieza no es tuya!" << std::endl;
				}
				return (i >= 0 && i < (TOTAL_PIECES / 2));
			}
		}
	}

	std::cout << "No hay ninguna pieza ahi!" << std::endl;

	return false;
}

//Función que sirve sobre todo para el enroque, ya que el rey no se puede enrocar si hay una pieza atacando su paso hacia este
bool caminoDespejado(Position casillaInicial, Position casillaFinal, std::vector<Pieces>& listPiecePos, int jugadorAtacante) {
	
	int step = (casillaFinal.y > casillaInicial.y) ? 1 : -1;

	Position casillaActual;

	casillaActual.x = casillaInicial.x;

	for (int i = casillaInicial.y; i <= casillaFinal.y; i += step)
	{
		casillaActual.y = i;

		if (casillaAtacada(casillaActual, jugadorAtacante, listPiecePos))
		{
			return false;
		}
	}

	return true;
}

//Función para saber si una pieza puede atacar ujna casilla es imprescindible para el jaque (ayuda de la IA, aquí gracias a ella fue la primera vez que pensé en la implementación del switch case para el ajedrez y descubrí toupper() y abs())
bool puedeAtacar(Position& posPieza, char tipoPieza, Position& casillaAComprobar, std::vector<Pieces>& listPiecePos) 
{
	int dx = abs(casillaAComprobar.x - posPieza.x), dy = abs(casillaAComprobar.y - posPieza.y);

	switch (toupper(tipoPieza)) {
	case 'P':
		if (tipoPieza == BLACK_PAWN) {
			return (casillaAComprobar.x == posPieza.x + 1 && dy == 1);
		}
		else {
			return (casillaAComprobar.x == posPieza.x - 1 && dy == 1);
		}

	case 'T':
		return ((posPieza.x == casillaAComprobar.x || posPieza.y == casillaAComprobar.y) && !piezaEnMedio(posPieza, casillaAComprobar, tipoPieza, listPiecePos, true, false));

	case 'H':
		return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);

	case 'B': 
		return (dx == dy) && dx > 0 && !piezaEnMedio(posPieza, casillaAComprobar, tipoPieza, listPiecePos, true, false);

	case 'Q': 
		return ((posPieza.x == casillaAComprobar.x || posPieza.y == casillaAComprobar.y || dx == dy) && !piezaEnMedio(posPieza, casillaAComprobar, tipoPieza, listPiecePos, true, false));

	case 'K': 
		return dx <= 1 && dy <= 1;

	default:
		return false;
	}
}

//Función para comprobar si hay jaque
bool jaque(std::vector<Pieces>& listPiecesPos, int jugador) {
	int idRey = encontrarRey(listPiecesPos, jugador);
	if (idRey == -1) return false;

	Position posRey = listPiecesPos[idRey].pos;
	int jugadorAtacante = (jugador == JUGADOR1) ? JUGADOR2 : JUGADOR1;

	return casillaAtacada(posRey, jugadorAtacante, listPiecesPos);
}

//Función para comprobar si una pieza tiene movimientos legales (la usaremos en la comprobación del jaque mate y en la comprobación de tablas por ahogado)
bool tieneMovimientosLegales(std::vector<Pieces>& listPiecePos, int idPieza, int jugador) {
	

	std::vector<Position> movimientosPosibles;
	std::vector<Pieces> copiaPiezas = listPiecePos;
	bool movimientoValido = false;

	//Si la pieza que queremos comprobar ha sido comida ni lo miramos
	if (!listPiecePos[idPieza].active)
	{
		return false;
	}
	else if (playerOwnsPiece(listPiecePos[idPieza].pos.x, listPiecePos[idPieza].pos.y, listPiecePos, jugador, idPieza))
	{
		//En funcion de la pieza la mandamos a una funcion diferente

		char tipo = toupper(listPiecePos[idPieza].piece);

		switch (tipo)
		{
		case 'P':
			generarMovimientosPeon(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;

		case 'T':
			generarMovimientosTorre(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;
		case 'H':
			generarMovimientosCaballo(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;

		case 'B':
			generarMovimientosAlfil(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;

		case 'Q':
			generarMovimientosReina(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;

		case 'K':
			generarMovimientosRey(listPiecePos[idPieza], jugador, movimientosPosibles);
			break;

		default:
			break;
		}
	}

	//Para cada uno de los movimientos posibles comprobamos si es válido
	for (size_t i = 0; i < movimientosPosibles.size(); i++)
	{
		bool comer = false, enroque = false;

		Position destino = movimientosPosibles[i];

		validarMovimientoSimulado(copiaPiezas, idPieza, destino, jugador, movimientoValido, comer, enroque);

		//Si encontramos un sólo movimiento válido retornamos true
		if (movimientoValido)
		{
			return true;
		}
	}
	//Si llegamos hasta aquí es porque ningún movimiento es válido
	if (!movimientoValido)
	{
		return false;
	}

	return false;
}

//Función para comprobar si hay jaque mate
bool jaqueMate(std::vector<Pieces>& listPiecesPos, int jugador) {
	
	// 1. Verificamos que el rey está en jaque
	if (!jaque(listPiecesPos, jugador)) {
		return false;
	}

	// 2. Encontramos la posición actual del rey
	int idRey = encontrarRey(listPiecesPos, jugador);
	if (idRey == -1) return false;

	// 3. Verificamos si el rey tiene movimientos legales
	if (tieneMovimientosLegales(listPiecesPos, idRey, jugador)) {
		return false;
	}

	// 4. Verificamos si alguna otra pieza puede bloquear el jaque (ayuda de la IA)
	for (int i = (jugador == JUGADOR1 ? 16 : 0); i < (jugador == JUGADOR1 ? 32 : 16); ++i) 
	{
		if (i == idRey || !listPiecesPos[i].active)
		{
			continue;
		}

		std::vector<Position> movimientos;
		char tipo = toupper(listPiecesPos[i].piece);

		switch (tipo) {
		case 'P': 
			generarMovimientosPeon(listPiecesPos[i], jugador, movimientos); 
			break;
		case 'T': 
			generarMovimientosTorre(listPiecesPos[i], jugador, movimientos); 
			break;
		case 'H': 
			generarMovimientosCaballo(listPiecesPos[i], jugador, movimientos); 
			break;
		case 'B': 
			generarMovimientosAlfil(listPiecesPos[i], jugador, movimientos); 
			break;
		case 'Q': 
			generarMovimientosReina(listPiecesPos[i], jugador, movimientos); 
			break;
		case 'K': 
			generarMovimientosRey(listPiecesPos[i], jugador, movimientos); 
			break;
		}

		//(IA). Pero entiendo lo que hace, está buscando si después de mover alguna pieza del jugador la jugada acaba en jaque y si encuentra una que no, es que el rey puede cubrirse o moverse, de lo contrario será jaque mate
		for (Position& destino : movimientos) {
			std::vector<Pieces> copia = listPiecesPos;
			bool valido = false, comer = false, enroque = false;

			validarMovimientoSimulado(copia, i, destino, jugador, valido, comer, enroque);

			if (valido) {

				if (!jaque(copia, jugador)) {
					return false;
				}
			}
		}
	}

	return true;
}

//Comprobamos tablas por ahogado (ninguna pieza tiene movimientos legales y el rey NO está en jaque)
bool tablasPorAhogado(std::vector<Pieces> listPiecePos, int jugador) {
	if (jaque(listPiecePos, jugador))
	{
		return false;
	}

	for (int i = 0; i < listPiecePos.size(); i++)
	{
		if (listPiecePos[i].active && playerOwnsPiece(listPiecePos[i].pos.x, listPiecePos[i].pos.y, listPiecePos, jugador, i))
		{
			//Si alguna pieza tiene movimientos legales, no hay tablas
			if (tieneMovimientosLegales(listPiecePos, i, jugador))
			{
				return false;
			}
		}
	}

	return true;
}

//Funcion para contar el material, sólo hay cuatro casos de tablas por falta de material
bool tablasPorFaltadeMaterial(std::vector<Pieces> listPiecePos) {
	
	int piezasBlancas = 0, piezasNegras = 0;

	bool alfilBlanco = false, caballoBlanco = false, alfilNegro = false, caballoNegro = false;

	std::vector<int> alfiles;

	for (int i = 0; i < listPiecePos.size(); i++)
	{
		if (listPiecePos[i].active)
		{
			char tipo = toupper(listPiecePos[i].piece);

			if (isupper(listPiecePos[i].piece))
			{
				piezasBlancas++;

				if (tipo == 'B')
				{
					alfilBlanco = true;
				}

				if (tipo == 'H')
				{
					caballoBlanco = true;
				}
			}
			else
			{
				piezasNegras++;

				if (tipo == 'B')
				{
					alfilNegro = true;
				}

				if (tipo == 'H')
				{
					caballoNegro = true;
				}
			}

			if (tipo == 'B')
			{
				alfiles.push_back(i);
			}
		}
	}

	//Rey vs Rey
	if (piezasBlancas == 1 && piezasNegras == 1)
	{
		return true;
	}

	//Rey + alfil vs Rey
	if ((piezasBlancas == 2 && piezasNegras == 1 && alfilBlanco) || (piezasNegras == 2 && piezasBlancas == 1 && alfilNegro))
	{
		return true;
	}

	//Rey + caballo vs Rey
	if ((piezasBlancas == 2 && piezasNegras == 1 && caballoBlanco) || (piezasNegras == 2 && piezasBlancas == 1 && caballoNegro))
	{
		return true;
	}

	// Rey + alfil vs Rey + alfil (alfil del mismo color)

	if (piezasBlancas == 2 && piezasNegras == 2 && alfilBlanco && alfilNegro && alfiles.size() == 2)
	{
		return (((listPiecePos[alfiles[0]].pos.x + listPiecePos[alfiles[0]].pos.y) % 2) == ((listPiecePos[alfiles[1]].pos.x + listPiecePos[alfiles[1]].pos.y) % 2)); 
	}

	return false;
}

//Gracias a habernos guardado el historial de la partida con la clave es súmamente sencillo comprobar si el tablero se ha repetido en 3 ocasiones mientras juega el mismo jugador
bool tablasPorRepeticion(std::vector<std::string>& historialPosiciones) {

	//Si el historial < 3 significa que todavía no ha habido al menos 3 jugadas por lo que no tiene sentido comprobarlo
	if (historialPosiciones.size() < 3)
	{
		return false;
	}
	std::string ultimaPosicion = historialPosiciones.back();

	//Contamos la última como una repetición ya que no itereamos sobre ella en el bucle
	int repeticiones = 1; 

	for (int i = 0; i < historialPosiciones.size() - 1; i++)
	{
		if (historialPosiciones[i] == ultimaPosicion)
		{
			repeticiones++;
		}

		if (repeticiones >= 3)
		{
			return true;
		}
	}

	return false;
}

//Hemos definido contador50movimientos para que si se mueve un peón o se realiza una captura se ponga a 0, por lo que si llega a 50 sabremos que cumple las condiciones
bool tablasPor50Movimientos(int& contador50Movimentos) {

	return (contador50Movimentos >= 50);
}

//Función principal de tablas, comprobamos si alguna de las funciones de tablas devuelve true, y en tal caso establecemos el caso y retornamos true
bool tablas(std::vector<Pieces> listPiecesPos, int jugador, int& contador50Movimientos, std::vector<std::string>& historialPosiciones, int& tipoTablas) {
	
	if (tablasPorAhogado(listPiecesPos, jugador))
	{
		tipoTablas = 1;
		return true;
	}
	else if (tablasPorFaltadeMaterial(listPiecesPos))
	{
		tipoTablas = 2;
		return true;
	}
	else if (tablasPorRepeticion(historialPosiciones))
	{
		tipoTablas = 3;
		return true;
	}
	else if (tablasPor50Movimientos(contador50Movimientos))
	{
		tipoTablas = 4;
		return true;
	}
	else
	{
		tipoTablas = 0;
		return false;
	}
	
	tipoTablas = 0;
	return false;
}

//Las comprobaciones referentes a los peones y al alfil me ha ayudado la IA. Estoy pensando si cambiar el resto para hacerlo más limpio, me he fijado que en vez de usar ifs camba movimientoValido por la comparación, lo que obtiene el mismo resultado más limpio.
void validarMovimiento(std::vector<Pieces>& listPiecePos, int idPieza, int jugador, bool& comer, bool& movimientoValido, Position& casillaFinal, bool& enroque, int& contador50Movimientos) {
	
	int idPiezaComida, x, y, tij2 = 0, tdj2 = 7, tij1 = 16, tdj1 = 23;
	bool salidaMaxima = false, torreMovida = true;
	comer = false;

	Position casillaInicial = { listPiecePos[idPieza].pos.x, listPiecePos[idPieza].pos.y }, casillaFinalEnroque;
	
	
	std::cout << "Introduce la casilla a la que moveras (fila y columna): ";

	do
	{
		movimientoValido = true;

		//Preguntamos por una casilla a la que mover hasta que se introduzca una válida (por tamaño del tablero)
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
			if (idPiezaComida >= (TOTAL_PIECES / 2) && idPiezaComida < TOTAL_PIECES)
			{
				movimientoValido = false;
			}
		}
		else if (jugador == JUGADOR2 && comer)
		{
			if (idPiezaComida >= 0 && idPiezaComida < (TOTAL_PIECES / 2))
			{
				movimientoValido = false;
			}
		}

		int jugadorAtacante = (jugador == JUGADOR1) ? JUGADOR2 : JUGADOR1;

		if (movimientoValido)
		{
			//El movimiento de los peones lo podía haber hecho con una variable int step = (jugador == JUGADOR1) ? -1 : 1; Pero era un momento temprano del desarrollo y todavía no había usado IA
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
			// Movimiento del alfil (ayuda IA)
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
			//Movimiento de la torre
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
			//Movimiento del caballo
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
			//Movimiento del rey (incluye enroque)
			else if (listPiecePos[idPieza].piece == BLACK_KING || listPiecePos[idPieza].piece == WHITE_KING)
			{
				if ((((x == listPiecePos[idPieza].pos.x || x == listPiecePos[idPieza].pos.x - 1 || x == listPiecePos[idPieza].pos.x + 1) && (y == listPiecePos[idPieza].pos.y || y == listPiecePos[idPieza].pos.y - 1 || y == listPiecePos[idPieza].pos.y + 1)) && !(x == listPiecePos[idPieza].pos.x && y == listPiecePos[idPieza].pos.y) && !casillaAtacada(casillaFinal, jugadorAtacante, listPiecePos)) && !piezaEnMedio(casillaInicial, casillaFinal, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima))
				{
					movimientoValido = true;
				}
				else if (!listPiecePos[idPieza].moved && !jaque(listPiecePos, jugador))
				{
					if (listPiecePos[idPieza].pos.x == x)
					{
						if (listPiecePos[idPieza].pos.y - 2 == y)
						{
							if (!listPiecePos[tij2].moved && jugador == JUGADOR2)
							{
								casillaFinalEnroque = { 0,0 };
								torreMovida = false;
							}
							else if (!listPiecePos[tij1].moved && jugador == JUGADOR1)
							{
								casillaFinalEnroque = { 7,0 };
								torreMovida = false;
							}
							else
							{
								movimientoValido = false;
								casillaFinalEnroque = {};

							}

							if (!piezaEnMedio(casillaInicial, casillaFinalEnroque, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima) && caminoDespejado(casillaInicial, casillaFinal, listPiecePos, jugadorAtacante) && !torreMovida)
							{
								movimientoValido = true;
								enroque = true;
							}
							else
							{
								movimientoValido = false;
							}
						}
						else if (listPiecePos[idPieza].pos.y + 2 == y)
						{
							if (!listPiecePos[tdj1].moved && jugador == JUGADOR1)
							{
								casillaFinalEnroque = { 7,7 };
								torreMovida = false;
							}
							else if (!listPiecePos[tdj2].moved && jugador == JUGADOR2)
							{
								casillaFinalEnroque = { 0,7 };
								torreMovida = false;
							}
							else
							{
								movimientoValido = false;
								casillaFinalEnroque = {};
							}

							if (!piezaEnMedio(casillaInicial, casillaFinalEnroque, listPiecePos[idPieza].piece, listPiecePos, comer, salidaMaxima) && caminoDespejado(casillaInicial, casillaFinal, listPiecePos, jugadorAtacante) && !torreMovida)
							{
								movimientoValido = true;
								enroque = true;
							}
							else
							{
								movimientoValido = false;
							}
						}
						else
						{
							movimientoValido = false;
						}
					}
					else
					{
						movimientoValido = false;
					}
				}
				else
				{
					movimientoValido = false;
				}
			}
			//Movimiento de la reina (mezcla alfil y torre)
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

		//Condiciones para el contador50movimientos
		if (movimientoValido && ((listPiecePos[idPieza].piece == BLACK_PAWN || listPiecePos[idPieza].piece == WHITE_PAWN) || comer))
		{
			contador50Movimientos = 0;
		}
		else if (movimientoValido)
		{
			contador50Movimientos++;
		}

		if (!movimientoValido)
		{
			break;
		}

	} while (!movimientoValido);

}