//enee14_sudoku.h

#ifndef ENEE140_GEN_SUDOKU_ENEE140_SUDOKU_H
#define ENEE140_GEN_SUDOKU_ENEE140_SUDOKU_H

int blanks;

int is_valid_board(int board[9][9]);

void new_sudoku_board(int board[9][9], int blanks);

void transform_permute_rows(int board[9][9]);

void transform_permute_bands(int board[9][9]);

void transform_permute_columns(int board[9][9]);

void transform_permute_stacks(int board[9][9]);

void transform_flip_main_diagonal(int board[9][9]);

void transform_flip_minor_diagonal(int board[9][9]);

void permute(int arr[], int n);

int print_sudoku_board(int board[9][9]);

int read_sudoku_board(const char file_name[], int board[9][9]);

int write_sudoku_board(const char file_name[], int board[9][9]);

int row_index(int x, int z);

int col_index(int y);


#endif //ENEE140_GEN_SUDOKU_ENEE140_SUDOKU_H
