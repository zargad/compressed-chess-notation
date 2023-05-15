#ifndef PIECE_H
#define PIECE_H

#include <stdio.h>

enum PieceType {
	Empty = ' ',
	King = 'K',
	Queen = 'Q',
	Rook = 'R',
	Bishop = 'B',
	Knight = 'H',
	Pawn = 'P',
};
enum PieceColor {
	Black = 0,
	White = 1,
};
struct Piece {
	enum PieceType type;
	enum PieceColor color;
};

#define PIECE_EMPTY (struct Piece) {Empty, Black}

int print_piece(struct Piece self);


struct PiecePosition {
    size_t x;
    size_t y;
};

int get_column(struct PiecePosition self);

int get_row(struct PiecePosition self);

struct PiecePosition position_from(char column, char row);

void print_position(struct PiecePosition self);


#define INVALID_POSITION (struct PiecePosition) {8, 8};

#endif
