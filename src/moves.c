#include <stdbool.h>
#include <stdio.h>

#include "piece.h"
#include "board.h"


struct Moves {
    struct PiecePosition data[24];
    size_t size;
};

void add_move(struct Moves *self, struct PiecePosition move) 
{
    self->data[self->size] = move;
    self->size++;
}

bool add_legal_move(struct Moves *self, Board board, struct PiecePosition destination_position) 
{
    if (!is_valid_position(destination_position)) {
        return false;
    }
    struct Piece destination = get_piece(board, destination_position);
    if (destination.type == Empty) {
        add_move(self, destination_position);
        return true;
    }
    return false;
}
#define ADD_LEGAL_MOVE() add_legal_move(self, board, position)

bool add_legal_capture(struct Moves *self, Board board, enum PieceColor current_color, struct PiecePosition destination_position) 
{
    if (!is_valid_position(destination_position)) {
        return false;
    }
    struct Piece destination = get_piece(board, destination_position);
    if (destination.type != Empty && destination.color != current_color) {
        add_move(self, destination_position);
        return true;
    }
    return false;
    
}
#define ADD_LEGAL_CAPTURE() add_legal_capture(self, board, color, position)


void init_pawn_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  
{
    position.y += color == Black ? -1 : 1;
    ADD_LEGAL_MOVE();
    position.x -= 1;
    ADD_LEGAL_CAPTURE();
    position.x += 2;
    ADD_LEGAL_CAPTURE();
    position.x -= 1;
    if (color == White && position.y == 2 || color == Black && position.y == 5) {
        position.y += color == Black ? -1 : 1;
        ADD_LEGAL_MOVE();
    }
}


void init_knight_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  
{
    position.x += 1;
    position.y += 2;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x += 1;
    position.y -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y -= 2;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x -= 1;
    position.y -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x -= 2;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x -= 1;
    position.y += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y += 2;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x += 1;
    position.y += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
}


void init_straight_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  
{
    int i;
    i = 0;
    do {
        position.x++;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
    i = 0;
    do {
        position.x--;
        i--;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
    i = 0;
    do {
        position.y++;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
    i = 0;
    do {
        position.y--;
        i--;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
}


void init_diagonal_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  
{
    int i;
    i = 0;
    do {
        position.x++;
        position.y++;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
    position.y -= i;
    i = 0;
    do {
        position.x--;
        position.y++;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x += i;
    position.y -= i;
    i = 0;
    do {
        position.x++;
        position.y--;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x -= i;
    position.y += i;
    i = 0;
    do {
        position.x--;
        position.y--;
        i++;
    } while (ADD_LEGAL_MOVE());
    ADD_LEGAL_CAPTURE();
    position.x += i;
    position.y += i;
}


void init_king_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  
{
    position.y += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x -= 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.y += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
    position.x += 1;
    ADD_LEGAL_CAPTURE();
    ADD_LEGAL_MOVE();
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
        init_straight_moves(self, board, position, color);
        break;
    case Bishop:
        init_diagonal_moves(self, board, position, color);
        break;
    case Queen:
        init_straight_moves(self, board, position, color);
        init_diagonal_moves(self, board, position, color);
        break;
    case King:
        init_king_moves(self, board, position, color);
        break;
    }
}


void print_moves(struct Moves *self) 
{
    for (int i = 0; i < self->size; i++) {
        print_position(self->data[i]);
        printf(",");
    }
    printf("\n");
}
