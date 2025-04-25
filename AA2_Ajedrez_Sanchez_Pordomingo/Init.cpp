#include "Library.h"
#include "Const.h"
#include "utils.h"

//Inicializamos la lista de piezas con las piezas que habrá y las metemos en una lista
std::vector<char> initPieces() {
	std::vector<char> pieceList;
	char blackPieces[TOTAL_PIECES / 2] = { BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK,BLACK_PAWN,BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN, BLACK_PAWN };
	char whitePieces[TOTAL_PIECES / 2] = { WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP,  WHITE_KING, WHITE_QUEEN, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK,WHITE_PAWN,WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN, WHITE_PAWN };
	for (size_t i = 0; i < TOTAL_PIECES / 2; i++)
	{
		pieceList.push_back(blackPieces[i]);
	}

	for (size_t i = 0; i < TOTAL_PIECES / 2; i++)
	{
		pieceList.push_back(whitePieces[i]);
	}
	return pieceList;
}

//Inicializamos el tablero, nos ayudará en cada turno para "vaciarlo"
void initChessBoard(char chessboard[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if ((i + j) % 2 == 0)
			{
				chessboard[i][j] = WHITE_SQUARES;
			}
			else
			{
				chessboard[i][j] = BLACK_SQUARES;
			}
		}
	}
}

//Inicializamos la lista de posiciones en las que irán las piezas al comienzo de la partida.
std::vector<Position> initPosPieces(std::vector<char> pieceList) {
	std::vector<Position> Posiciones;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < TOTAL_PIECES/4; j++)
		{
			Posiciones.push_back({ i,j });
		}
	}

	for (int i = 7; i >= 6; i--)
	{
		for (int j = 0; j < TOTAL_PIECES / 4; j++)
		{
			Posiciones.push_back({ i,j });
		}
	}
	return Posiciones;
}

//Juntamos las listas de piezas y posiciones en una, además asignamos el valor active=true que nos permitirá diferenciar la piezas capturadas y no
std::vector<Pieces> initPieceList(std::vector<char> piecesList, std::vector<Position> positionList) {
	
	std::vector<Pieces> listPiecePos(TOTAL_PIECES);

	for (int i = 0; i < TOTAL_PIECES; i++)
	{
		listPiecePos[i].piece = piecesList[i];
		listPiecePos[i].pos = positionList[i];
		listPiecePos[i].active = true;
	}


	return listPiecePos;
}

//Funcion para imprimir tablero
void viewChessBoard(char chessboard[BOARD_SIZE][BOARD_SIZE]) {
	std::cout << ' ' << ' ';
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << i + 1 << ' ' ;
	}
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << BOARD_SIZE - i << ' ';
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			std::cout << chessboard[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}