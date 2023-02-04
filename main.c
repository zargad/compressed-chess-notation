#include<stdio.h>
#include<stdbool.h>
#include "utils.h"
#include "piece.h"
#include "board.h"
#include "moves.h"






int main()
{
	Board test_board;
	empty_board(&test_board);
	set_default(&test_board);
	print_board(test_board);
    struct PiecePosition temp = get_piece_position(test_board, 1, Black);
    print_position(temp);
}
