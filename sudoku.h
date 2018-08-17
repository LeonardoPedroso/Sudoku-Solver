#include <stdio.h>

#define EMPTY 0
#define POSSIBLE 1
#define NOT_POSSIBLE 2

#define INVALID 10
#define FULL 11

#define TRUE 1
#define FALSE 0

#define byte unsigned char

#define TABLE_LENGTH 9
#define TABLE_HEIGHT 9
#define TABLE_DEPTH 10

/*#define SUDOKU1 {0, 0, 9,   8, 0, 0,   0, 0, 7}
#define SUDOKU2	{8, 0, 0,   0, 0, 0,   0, 0, 0}
#define SUDOKU3	{0, 2, 4,   1, 0, 6,   0, 5, 0}

#define SUDOKU4	{0, 4, 0,   0, 0, 9,   0, 2, 0}
#define SUDOKU5 {0, 9, 2,   0, 0, 0,   7, 6, 0}
#define SUDOKU6 {0, 1, 0,   7, 0, 0,   0, 4, 0}

#define SUDOKU7 {0, 3, 0,   6, 0, 4,   5, 0, 0}
#define SUDOKU8 {0, 0, 0,   0, 0, 0,   0, 0, 2}
#define SUDOKU9 {9, 0, 0,   0, 0, 2,   6, 0, 0}

#define SUDOKU {SUDOKU1, SUDOKU2, SUDOKU3, SUDOKU4, SUDOKU5, SUDOKU6, SUDOKU7, SUDOKU8, SUDOKU9}*/


#define SUDOKU1 {0, 0, 0,   0, 5, 6,   0, 1, 2}
#define SUDOKU2	{0, 3, 0,   0, 0, 0,   0, 0, 4}
#define SUDOKU3	{2, 0, 1,   0, 0, 0,   0, 0, 0}

#define SUDOKU4	{6, 0, 0,   9, 0, 0,   8, 0, 0}
#define SUDOKU5 {8, 0, 0,   0, 0, 0,   6, 0, 3}
#define SUDOKU6 {0, 5, 3,   0, 0, 0,   0, 0, 1}

#define SUDOKU7 {0, 4, 0,   0, 1, 7,   0, 0, 0}
#define SUDOKU8 {7, 0, 6,   0, 0, 8,   0, 0, 0}
#define SUDOKU9 {0, 0, 0,   0, 0, 3,   0, 0, 0}

#define SUDOKU {SUDOKU1, SUDOKU2, SUDOKU3, SUDOKU4, SUDOKU5, SUDOKU6, SUDOKU7, SUDOKU8, SUDOKU9}

void init_table(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
void print_table(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte k);
void check_posssible_numbers(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
byte start_square(byte x);
void check_square(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte i, byte j, byte k, byte start_square_i, byte start_square_j );
byte fill_sudoku(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
byte reset_possible_numbers(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
byte clone_sudoku(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
void copy_table(byte table_to[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH], byte table_from[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);
byte check_sudoku_validity(byte table[TABLE_LENGTH][TABLE_HEIGHT][TABLE_DEPTH]);

