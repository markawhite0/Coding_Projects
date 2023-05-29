//enee140_gen_sudoku.c

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Error: too many or too few command-line arguments\n");
        printf("Usage: enee140_gen_sudoku filename options [difficulty]\n");
        return 1;
    }

    const char *filename = argv[1];
    unsigned int options = (unsigned int)atoi(argv[2]);
    char *difficulty = (argc == 4) ? argv[3] : NULL;

    int board[9][9];
    int blanks = 0;

    srand(time(NULL));

    if (difficulty) {
        if (strcmp(difficulty, "easy") == 0) {
            blanks = rand() % 15 + 31;
        } else if (strcmp(difficulty, "medium") == 0) {
            blanks = rand() % 6 + 46;
        } else if (strcmp(difficulty, "hard") == 0) {
            blanks = rand() % 10 + 52;
        } else {
            printf("Invalid difficulty level.\n");
            return 1;
        }
    } else {
        blanks = rand() % 31 + 31;
    }

    //Menu
    if (!(options & 1)) {
        new_sudoku_board(board, blanks);
    } else {
        if (read_sudoku_board(filename, board) != 0) {
            printf("Error: Cannot read the Sudoku board from the file.\n");
            return 1;
        }
        if (!is_valid_board(board)) {
            printf("Error: The provided Sudoku board is not valid.\n");
            return 1;
        }
    }

    if (options & (1 << 1)) {
        transform_permute_rows(board);
    }

    if (options & (1 << 2)) {
        transform_permute_bands(board);
    }

    if (options & (1 << 3)) {
        transform_permute_columns(board);
    }

    if (options & (1 << 4)) {
        transform_permute_stacks(board);
    }

    if (options & (1 << 5)) {
        transform_flip_main_diagonal(board);
    }

    if (options & (1 << 6)) {
        transform_flip_minor_diagonal(board);
    }

    if (options & (1 << 7)) {

        print_sudoku_board(board);
    }

    if (options & (1 << 8)) {
        write_sudoku_board(filename, board);
    }
    return 0;
}