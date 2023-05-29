//enee140_solve_sudoku.c

#include <stdio.h>
#include <time.h>
#include <ctype.h>


int solve_sudoku_board(int board[9][9]);

int print_sudoku_board(int board[9][9]);

int read_sudoku_board(const char file_name[], int board[9][9]);

int solve_sudoku(const char file_name[]);

int is_valid_move(int board[9][9], int row, int col, int num);

int find_empty_cell(int board[9][9], int *row, int *col);


int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    solve_sudoku(argv[1]);
    return 0;
}


int solve_sudoku_board(int board[9][9]) {
    int row, col, num;
    if (!find_empty_cell(board, &row, &col)){
        return 1; //No empty cell found, board is solved
    }
    for (num = 1; num <= 9; num++){
        if (is_valid_move(board, row, col, num)){
            board[row][col] = num;
            if (solve_sudoku_board(board)) {
                return 1;
            }
            board[row][col] = 0; //Undo the move and try another number
        }
    }
    return 0; //Backtrack
}


int print_sudoku_board(int board[9][9]){
    int x, z;
    for (x = 0; x < 9; x++){
        if (x % 3 == 0){
            printf("+-------+-------+-------+\n");
        }
        for (z = 0; z < 9; z++){
            if (z % 3 == 0){
                printf("| ");
            }
            if (board[x][z] < 0 || board[x][z] > 9){
                printf("Printing error: invalid numbers (other than 0–9) detected.\n");
                return -1;
            }
            if (board[x][z] == 0){
                printf("- ");
            } else{
                printf("%d ", board[x][z]);
            }
        }
        printf("|\n");
    }
    printf("+-------+-------+-------+\n");
    return 0;
}


int read_sudoku_board(const char file_name[], int board[9][9]){
    FILE *file = fopen(file_name, "r");

    if (file == NULL){
        printf("Input file error: Could not open the file.\n");
        return -1;
    }

    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            char ch;
            if (fscanf(file, " %c", &ch) != 1){
                fclose(file);
                printf("Input file error: Invalid file format. Not enough lines or lines too short.\n");
                return -3;
            }

            if (isspace(ch)){
                continue;
            }

            if (ch >= '1' && ch <= '9'){
                board[i][j] = ch - '0';
            } else if (ch == '-'){
                board[i][j] = 0;
            } else{
                fclose(file);
                printf("Input file error: Invalid character encountered, only 1-9 and \"-\" are allowed.\n");
                return -2;
            }
        }
    }

    // Check for extra characters
    char extra_char;
    if (fscanf(file, " %c", &extra_char) == 1){
        fclose(file);
        printf("Input file Error: Invalid file format. Too many characters.\n");
        return -4;
    }

    fclose(file);

    return 0;
}

int solve_sudoku(const char file_name[]){
    int board[9][9];
    int blanks = read_sudoku_board(file_name, board);
    if (blanks < 0){
        return -1;
    }
    printf("Input board:\n");
    print_sudoku_board(board);
    int tests = solve_sudoku_board(board);
    if (tests > 0) {
        printf("Solution:\n");
        print_sudoku_board(board);
        printf("%d board validity tests performed.\n", tests);
        return tests;
    } else {
        printf("This board cannot be solved.\n");
        return 0;
    }
}
int find_empty_cell(int board[9][9], int *row, int *col){
    for (*row = 0; *row < 9; (*row)++){
        for (*col = 0; *col < 9; (*col)++){
            if (board[*row][*col] == 0){
                return 1;
            }
        }
    }
    return 0;
}

int is_valid_move(int board[9][9], int row, int col, int num){
    int x, z, box_row, box_col;
    // Check row for duplicates
    for (z = 0; z < 9; z++) {
        if (board[row][z] == num){
            return 0;
        }
    }
    // Check column for duplicates
    for (x = 0; x < 9; x++){
        if (board[x][col] == num){
            return 0;
        }
    }
    // Check box for duplicates
    box_row = (row / 3) * 3;
    box_col = (col / 3) * 3;
    for (x = box_row; x < box_row + 3; x++){
        for (z = box_col; z < box_col + 3; z++){
            if (board[x][z] == num) {
                return 0;
            }
        }
    }
    return 1;
}
