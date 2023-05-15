#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

#include "utils.h"
#include "piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define BOARD_BACK_RANK "RHBQKBHR"
typedef struct Piece Board[BOARD_HEIGHT][BOARD_WIDTH];
void fill_region(Board *self, struct Region region, struct Piece piece);


struct Piece get_piece(Board self, struct PiecePosition position);


bool is_valid_position(struct PiecePosition position);


void empty_region(Board *self, struct Region region);

void empty_board(Board *self);

void empty_middle(Board *self);

void set_pawns(Board *self, enum PieceColor color);

void set_back_rank(Board *self, enum PieceColor color);

void set_color(Board *self, enum PieceColor color);

void set_default(Board *self);

int print_board(Board board);

#endif
