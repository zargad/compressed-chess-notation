#include<stdio.h>
#include<stdbool.h>


struct Range {
    int min;
    int max;
};

struct Range range_from_max(int max) 
{
    return (struct Range) {0, max};
}


struct Region {
    struct Range x;
    struct Range y;
};

struct Region region_from_max(int x, int y) 
{
    return (struct Region) {range_from_max(x), range_from_max(y)};
}

struct Region horizontal_region(int y, struct Range x)
{
    return (struct Region) {x, (struct Range) {y, y + 1}};
}

struct Region vertical_region(int x, struct Range y)
{
    return (struct Region) {(struct Range) {x, x + 1}, y};
}


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


#define INVALID_POSITION (struct PiecePosition) {8, 8};


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


struct Moves {
    struct PiecePosition data[24];
    size_t size;
};

void add_move(struct Moves *self, struct PiecePosition move) {
    self->data[self->size] = move;
    self->size++;
}


void init_pawn_moves(struct Moves *self, Board board, struct PiecePosition position, enum PieceColor color)  {
    position.y += color ? -1 : 1;
    add_move(self, position);
    if (position.y == 1 && color || position.y == 6 && !color) {
        position.y += color ? -1 : 1;
        add_move(self, position);
    }
}


void init_knight_moves(struct Moves *self, Board board, struct PiecePosition position)  {
}


void init_moves(struct Moves *self, Board board, struct PiecePosition position) 
{
    struct Piece piece = get_piece(board, position);
    switch (piece.type) {
    case Pawn:
        init_pawn_moves(self, board, position, piece.color);
        break;
    case Knight:
        init_knight_moves(self, board, position);
        break;
    case Rook:
        // init_straight_moves(self, board, position);
        break;
    case Bishop:
        // init_diagonal_moves(self, board, position);
        break;
    case Queen:
        // init_straight_moves(self, board, position);
        // init_diagonal_moves(self, board, position);
        break;
    case King:
        // init_king_moves(self, board, position);
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


int main()
{
	Board test_board;
	empty_board(&test_board);
	set_default(&test_board);
	print_board(test_board);
    struct PiecePosition temp = get_piece_position(test_board, 1, Black);
    print_position(temp);
}
