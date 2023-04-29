#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define BOARD_BACK_RANK "RHBQKBHR"
typedef struct Piece Board[BOARD_HEIGHT][BOARD_WIDTH];
void fill_region(Board *self, struct Region region, struct Piece piece)
{
	for (int y = region.y.min; y < region.y.max; y++) {
		for (int x = region.x.min; x < region.x.max; x++) {
			(*self)[y][x] = piece;
		}
	}
}


struct Piece get_piece(Board self, struct PiecePosition position) 
{
    return self[position.y][position.x];
}


bool is_valid_position(struct PiecePosition position)
{
    return (0 <= position.x && position.x < BOARD_WIDTH) && (0 <= position.y && position.y < BOARD_HEIGHT);
}


void empty_region(Board *self, struct Region region) 
{
    fill_region(self, region, PIECE_EMPTY); 
}

void empty_board(Board *self)
{
    empty_region(self, region_from_max(BOARD_WIDTH, BOARD_HEIGHT)); 
}

void empty_middle(Board *self) 
{
    const struct Region region = {{0, BOARD_WIDTH}, {2, BOARD_HEIGHT - 2}};
    empty_region(self, region); 
}

void set_pawns(Board *self, enum PieceColor color)
{
	const int y = color == Black ? BOARD_HEIGHT - 2 : 1;
    const struct Piece pawn = {Pawn, color};
    const struct Region region = horizontal_region(y, range_from_max(BOARD_WIDTH));
    fill_region(self, region, pawn);
}

void set_back_rank(Board *self, enum PieceColor color)
{
	const int y = color == Black ? BOARD_HEIGHT - 1 : 0;
	for (int x = 0; x < BOARD_WIDTH; x++) {
		(*self)[y][x] = (struct Piece) { BOARD_BACK_RANK[x], color };
	}
}

void set_color(Board *self, enum PieceColor color)
{
	set_back_rank(self, color);
	set_pawns(self, color);
}


void set_default(Board *self)
{
    empty_middle(self);
	set_color(self, Black);
	set_color(self, White);
}

int print_board(Board board)
{
	for (int y = BOARD_HEIGHT - 1; y >= 0; y--) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
            printf("\e[%sm", x%2 == y%2 ? "41" : "42");
			print_piece(board[y][x]);
		}
		printf("\n");
	}
}

#endif
