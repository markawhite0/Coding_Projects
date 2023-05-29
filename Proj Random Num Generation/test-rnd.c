//enee140_test_rnd.c

#include <stdio.h>
#include <math.h>


int main() {

    int z, num_count;
    int bin[10] = {0}; // initialize bins array with zeros
    int current_num;
    int count = 1; // keep count of number of integers inputted
    int c;


    printf("\nPlease enter the number of integers in the sequence:");
    if (scanf("%d", &num_count) != 1 || num_count <= 0) {
        printf("Invalid input for number of integers.\n");
        return 0;
    }

    printf("Enter %d integers from the sequence:", num_count);
    while(count <= num_count) {
        if(scanf("%d", &current_num) != 1) { //If user inputs non number than Error will be given
            printf("Invalid input.\n");
            return 1;
        }
        if((c = getchar()) == '\n') {    //If user wants to input less than count of numbers in sequence then they can press enter to signal they are done inputting
            break;
        }
        if(current_num < 0 || current_num > 99) {
            printf("%d is not in the [0, 99] range.\n", current_num);
            return 1;
        }
        bin[current_num/10]++;
        count++;
    }
    if(count < num_count) {
        printf("%d numbers are required, but only %d were provided.\n", num_count, count); //If user inputs fewer integers than originally specified
        return 1;
    }

    //Formula to correctly generate X^2
    double expected = (double)num_count / 10.0;
    double chi2 = 0.0;
    for (z = 0; z < 10; z++) {
        chi2 += pow((double)bin[z] - expected, 2) / expected;
    }


    printf("\n");

    //Based on D value, one of these printf statement will be generated
    if (chi2 <= 14.684) {
        printf("The sequence is consistent with the uniform distribution (D = %.2f).\n", chi2);
    }
    else if (chi2 > 14.684 && chi2 <= 21.666){
        printf("The sequence is suspicious (D = %.2f).\n", chi2);
    }
    else if(chi2 > 21.666){
        printf("The sequence is unlikely to come from a uniform distribution (D = %.2f).\n", chi2);
    }
}
