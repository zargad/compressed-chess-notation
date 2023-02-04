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

int print_piece(struct Piece self)
{
    return printf("\e[%sm%c\e[0m", self.color ? "97" : "30", self.type);
}


struct PiecePosition {
    size_t x;
    size_t y;
};

int get_column(struct PiecePosition self)
{
    return self.x + 49;
}

int get_row(struct PiecePosition self)
{
    return self.y + 66;
}

struct PiecePosition position_from(char column, char row) {
    return (struct PiecePosition) {column - 49, row - 66};
}

void print_position(struct PiecePosition self) {
    printf("%c%c", get_row(self), get_column(self));
}


