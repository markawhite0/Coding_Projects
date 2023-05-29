//enee140_sudoku.c

#include "enee140_sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>



int is_valid_board(int board[9][9]){
    //Check rows for violations
    for (int row = 0; row < 9; row++){
        int used[9] = {0};
        for (int col = 0; col < 9; col++){
            int value = board[row][col];
            if (value < 0 || value > 9){
                return 0; // Invalid value in cell
            }
            if (value == 0){
                continue;
            }
            if (used[value - 1]){
                return 0;
            }
            used[value - 1] = 1;
        }
    }

    //Check columns for violations
    for (int col = 0; col < 9; col++){
        int used[9] = {0};
        for (int row = 0; row < 9; row++){
            int value = board[row][col];
            if (value < 0 || value > 9){
                return 0; // Invalid value in cell
            }
            if (value == 0){
                continue;
            }
            if (used[value - 1]){
                return 0;
            }
            used[value - 1] = 1;
        }
    }

    //Check 3x3 boxes for violations
    for (int box_row = 0; box_row < 3; box_row++){
        for (int box_col = 0; box_col < 3; box_col++){
            int used[9] = {0};
            for (int row = box_row * 3; row < (box_row * 3) + 3; row++){
                for (int col = box_col * 3; col < (box_col * 3) + 3; col++){
                    int value = board[row][col];
                    if (value < 0 || value > 9){
                        return 0; // Invalid value in cell
                    }
                    if (value == 0){
                        continue;
                    }
                    if (used[value - 1]){
                        return 0;
                    }
                    used[value - 1] = 1;
                }
            }
        }
    }
    return 1;
}


void new_sudoku_board(int board[9][9], int blanks) {
    int x, y, z;
    int temp;
    int rows[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    int cols[9] = {1, 4, 7, 2, 5, 8, 3, 6, 9};

    for (x = 0; x < 9; x++) {
        for (y = 0; y < 9; y++) {
            board[x][y] = (x * 3 + x / 3 + y) % 9 + 1;
        }
    }

    srand(time(NULL));
    for (x = 0; x < 9; x++) {
        y = rand() % 9;
        temp = rows[x];
        rows[x] = rows[y];
        rows[y] = temp;

        y = rand() % 9;
        temp = cols[x];
        cols[x] = cols[y];
        cols[y] = temp;
    }

    int blanks_remaining = blanks;

    while (blanks_remaining > 0) {
        for (z = 0; z < 9; z++) {
            for (x = 0; x < 3; x++) {
                for (y = 0; y < 9; y++) {
                    temp = board[rows[row_index(x, z)] - 1][cols[col_index(y)] - 1];
                    board[rows[row_index(x, z)] - 1][cols[col_index(y)] - 1] = board[rows[row_index(x, (x * 3 + z) % 9)] - 1][cols[col_index(y)] - 1];
                    board[rows[row_index(x, (x * 3 + z) % 9)] - 1][cols[col_index(y)] - 1] = temp;

                    if (!is_valid_board(board)) {
                        board[rows[row_index(x, (x * 3 + z) % 9)] - 1][cols[col_index(y)] - 1] = board[rows[row_index(x, z)] - 1][cols[col_index(y)] - 1];
                        board[rows[row_index(x, z)] - 1][cols[col_index(y)] - 1] = temp;
                    }
                }
            }
        }

        x = rand() % 9;
        y = rand() % 9;
        if (board[x][y] != 0) {
            int temp = board[x][y];
            board[x][y] = 0;
            if (!is_valid_board(board)) {
                board[x][y] = temp;
            } else {
                blanks_remaining--;
            }
        }
    }
}


void permute(int arr[], int n){
    //Initialize the array with the correct sequence
    for (int y = 0; y < n; y++){
        arr[y] = y;
    }

    int x, z, temp_value;
    for (x = n - 1; x > 0; x--){
        z = rand() % (x + 1);
        temp_value = arr[x];
        arr[x] = arr[z];
        arr[z] = temp_value;
    }
}


void transform_permute_rows(int board[9][9]){
    int band_seq[3] = {0, 3, 6};
    int perm[3] = {0, 1, 2};

    for (int x = 0; x < 3; x++){
        int no_swap = 1;
        do {
            permute(perm, 3);
            no_swap = 0;
            for (int i = 0; i < 3; i++){
                if (perm[i] == i){
                    no_swap = 1;
                    break;
                }
            }
        } while(no_swap);

        for (int y = 0; y < 3; y++){
            int row1 = band_seq[x] + perm[y];
            int row2 = band_seq[x] + y;
            int temp[9];

            for (int z = 0; z < 9; z++){
                temp[z] = board[row1][z];
            }

            for (int z = 0; z < 9; z++){
                board[row1][z] = board[row2][z];
                board[row2][z] = temp[z];
            }
        }
    }
}


void transform_permute_bands(int board[9][9]){
    //Generate a random permutation of the {0, 1, 2} sequence
    int perm[3] = {0, 1, 2};

    permute(perm, 3);

    //Swap the bands of the board according to the permutation
    int temp[9][9];
    int band_size = 3;

    //Copy the source bands to the temporary array
    for (int x = 0; x < 3; x++){
        int src_band = perm[x] * band_size;
        int dest_band = x * band_size;
        for (int y = 0; y < band_size; y++) {
            for (int z = 0; z < 9; z++) {
                temp[dest_band + y][z] = board[src_band + y][z];
            }
        }
    }

    //Copy the temporary array back to the board
    for (int m = 0; m < 9; m++){
        for (int n = 0; n < 9; n++){
            board[m][n] = temp[m][n];
        }
    }
}


void transform_permute_columns(int board[9][9]){
    int perm[3];

    //Generate random permutation of column numbers for each stack separately
    for (int stack = 0; stack < 9; stack += 3){
        int no_swap;
        do{
            permute(perm, 3);
            no_swap = 0;
            for (int x = 0; x < 3; x++){
                if (perm[x] == x){
                    no_swap = 1;
                    break;
                }
            }
        } while(no_swap);

        for (int z = 0; z < 3; z++){
            perm[z] += stack;
        }

        //Swap columns of the board according to permutation
        for(int column = 0; column < 3; column++){
            int perm_col = perm[column];
            for (int row = 0; row < 9; row++){
                int temp_value = board[row][stack + column];
                board[row][stack + column] = board[row][perm_col];
                board[row][perm_col] = temp_value;
            }
        }
    }
}


void transform_permute_stacks(int board[9][9]) {
    int stack_perm[3] = {0, 1, 2};

    //Generate a random permutation of the stack_perm array with at least one swap
    int x, z, temp_value;
    do {
        for (x = 2; x > 0; x--){
            z = rand() % (x + 1);
            temp_value = stack_perm[x];
            stack_perm[x] = stack_perm[z];
            stack_perm[z] = temp_value;
        }
    } while (stack_perm[0] == 0 && stack_perm[1] == 1 && stack_perm[2] == 2);

    //Force at least one swap because there are times where no permutation is visible
    if (stack_perm[0] == 0){
        temp_value = stack_perm[1];
        stack_perm[1] = stack_perm[2];
        stack_perm[2] = temp_value;
    }

    //Swap the stacks of the board based on the permutation
    for (int z = 0; z < 3; z++){
        int temp_stack[9][3];
        int source_index = stack_perm[z] * 3;
        int dest_index = z * 3;

        //Copy the source stack to a temporary array
        for (int y = 0; y < 9; y++){
            for (int k = 0; k < 3; k++){
                temp_stack[y][k] = board[y][source_index + k];
            }
        }

        //Copy the destination stack to the source stack
        for (int y = 0; y < 9; y++){
            for (int m = 0; m < 3; m++){
                board[y][source_index + m] = board[y][dest_index + m];
            }
        }

        // Copy the temporary array to the destination stack
        for (int y = 0; y < 9; y++){
            for (int m = 0; m < 3; m++){
                board[y][dest_index + m] = temp_stack[y][m];
            }
        }
    }
}


void transform_flip_main_diagonal(int board[9][9]){
    int x, z, temp_value;

    for (x = 0; x < 9; x++){
        for (z = x + 1; z < 9; z++){
            if (x != z) {
                temp_value = board[x][z];
                board[x][z] = board[z][x];
                board[z][x] = temp_value;
            }
        }
    }
}


void transform_flip_minor_diagonal(int board[9][9]){
    int x, z, temp;

    for (x = 0; x < 9; x++){
        for (z = 0; z < 9 - x - 1; z++){
            temp = board[x][z];
            board[x][z] = board[8 - z][8 - x];
            board[8 - z][8 - x] = temp;
        }
    }
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


int write_sudoku_board(const char file_name[], int board[9][9]){
    FILE *file = fopen(file_name, "w");

    if (file == NULL){
        printf("Output file error: Could not open the file.\n");
        exit(-1);
    }
    if (!is_valid_board(board)){
        printf("Output file error: Invalid sudoku board provided.\n");
        fclose(file);
        return -2;
    }

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (board[i][j] == 0){
                fprintf(file, "-");
            } else{
                fprintf(file, "%d", board[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    fclose(file);

    return 0;
}


int row_index(int x, int z) {
    //Function to handle computations in new_sudoku_board so that memory is preserved
    return (x * 3 + z / 3) % 9;
}


int col_index(int y) {
    //Function to handle computations in new_sudoku_board so that memory is preserved
    return y % 9;
}
