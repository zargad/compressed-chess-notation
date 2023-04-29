#ifndef MOVES_H
#define MOVES_H

#include "piece.h"
#include "board.h"

struct Moves {
    struct PiecePosition data[24];
    size_t size;
};

void add_move(struct Moves *self, struct PiecePosition move);

void add_legal_move(struct Moves *self, Board board, enum PieceColor current_color, struct PiecePosition destination_position);


void init_pawn_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color);

void init_knight_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color);


void init_moves(struct Moves *self, Board board, struct PiecePosition position);


int get_piece_index(Board self, struct PiecePosition position);

struct PiecePosition get_piece_position(Board self, int index, enum PieceColor color);


void print_moves(struct Moves *self);

#endif
