#include <stdio.h>

#include "piece.h"
#include "board.h"


struct Moves {
    struct PiecePosition data[24];
    size_t size;
};

void add_move(struct Moves *self, struct PiecePosition move) {
    self->data[self->size] = move;
    self->size++;
}

void add_legal_move(struct Moves *self, Board board, enum PieceColor current_color, struct PiecePosition destination_position) {
    struct Piece destination = get_piece(board, destination_position);
    if (destination.type == Empty || destination.color != current_color) {
        add_move(self, destination_position);
    }
    
}


void init_pawn_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  {
    position.y += color ? -1 : 1;
    if (color && position.y == 1 || !color && position.y == 6) {
        position.y += color ? -1 : 1;
        add_move(self, position);
    }
}


void init_knight_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  {
}


void init_moves(struct Moves *self, Board board, struct PiecePosition position) 
{
    struct Piece piece = get_piece(board, position);
    enum PieceColor color = piece.color;
    switch (piece.type) {
    case Pawn:
        init_pawn_moves(self, board, position, color);
        break;
    case Knight:
        init_knight_moves(self, board, position, color);
        break;
    case Rook:
        // init_straight_moves(self, board, position, color);
        break;
    case Bishop:
        // init_diagonal_moves(self, board, position, color);
        break;
    case Queen:
        // init_straight_moves(self, board, position, color);
        // init_diagonal_moves(self, board, position, color);
        break;
    case King:
        // init_king_moves(self, board, position, color);
        break;
    }
}


int get_piece_index(Board self, struct PiecePosition position)
{
    struct Piece piece = get_piece(self, position);
    if (piece.type == Empty) {
        return -1;
    }
    enum PieceColor color = piece.color;
    int index = 0;
    struct Piece current_piece;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            current_piece = self[y][x];
            if (y == position.y && x == position.x) {
                return index;
            } else if (current_piece.type != Empty && current_piece.color == color) {
                index++;
            }
        }
    }
    return -1;
}

struct PiecePosition get_piece_position(Board self, int index, enum PieceColor color)
{
    struct Piece current_piece;
    for (int y = 0; y < BOARD_HEIGHT; y++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            current_piece = self[y][x];
            if (current_piece.type != Empty && current_piece.color == color) {
                if (index == 0) {
                    return (struct PiecePosition) {x, y};
                }
                index--;
            }
        }
    }
    return INVALID_POSITION;
}
