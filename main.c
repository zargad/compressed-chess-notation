#include<stdio.h>


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
	const int y = color ? BOARD_HEIGHT - 2 : 1;
    const struct Piece pawn = {Pawn, color};
    const struct Region region = horizontal_region(y, range_from_max(BOARD_WIDTH));
    fill_region(self, region, pawn);
}

void set_back_rank(Board *self, enum PieceColor color)
{
	const int y = color ? BOARD_HEIGHT - 1 : 0;
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
	for (int y = 0; y < BOARD_HEIGHT; y++) {
		for (int x = 0; x < BOARD_WIDTH; x++) {
            printf("\e[%sm", x%2 == y%2 ? "41" : "42");
			print_piece(board[y][x]);
		}
		printf("\n");
	}
}

int main()
{
	Board test_board;
	empty_board(&test_board);
	set_default(&test_board);
	print_board(test_board);
}
