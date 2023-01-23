#include<stdio.h>


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
struct Piece get_empty_piece() {
    return (struct Piece) { Empty, Black };
}
int print_piece(struct Piece self) {
    if (self.color) {
        return printf("\e[97m%c\e[0m", self.type);
    }
    return printf("\e[30m%c\e[0m", self.type);
}



#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
typedef struct Piece Board[BOARD_HEIGHT][BOARD_WIDTH];
void empty_board(Board *self) {
    for (int y=0; y<BOARD_HEIGHT; y++) {
        for (int x=0; x<BOARD_WIDTH; x++) {
            (*self)[y][x] = get_empty_piece();
        }
    }
}
void _set_back_rank(Board *self, enum PieceColor color) {
    int y = color ? 7 : 0;
    #define BACK_RANK "RHBQKBHR"
    for (int x=0; x<BOARD_WIDTH; x++) {
        (*self)[y][x] = (struct Piece) { BACK_RANK[x], color };
    }
}
void _set_pawns(Board *self, enum PieceColor color) {
    int y = color ? 6 : 1;
    for (int x=0; x<BOARD_WIDTH; x++) {
        (*self)[y][x] = (struct Piece) { 'P', color };
    }
}
void _set_color(Board *self, enum PieceColor color) {
    _set_back_rank(self, color);
    _set_pawns(self, color);
}
void set_default(Board *self) {
    _set_color(self, Black);
    _set_color(self, White);
}
int print_board(Board board) {
    for (int y=0; y<BOARD_HEIGHT; y++) {
        for (int x=0; x<BOARD_WIDTH; x++) {
            if (x%2 == y%2) {
                printf("\e[41m");
            } 
            else {
                printf("\e[42m");
            }
            print_piece(board[y][x]);
        }
        printf("\n");
    }
}


int main() {
    Board test_board;
    empty_board(&test_board);
    set_default(&test_board);
    // test_board[0][0] = (struct Piece) { King, White };
    print_board(test_board);
}
