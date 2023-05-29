//enee140_test_rnd_exp.c

#include <stdio.h>
#include <math.h>

#define NUM_BINS 10

//Function for the formula to calculate CDF
double calculate_cdf(double x);

int main() {

    int num_count;
    int bin[NUM_BINS] = {0}; // initialize bins array with zeros
    double current_num;
    int count = 1; // keep count of number of doubles inputted
    int c;

    printf("\nPlease enter the number of numbers in the sequence: ");
    if (scanf("%d", &num_count) != 1 || num_count <= 0) {
        printf("Invalid input for number of doubles.\n");
        return 0;
    }

    printf("Enter %d numbers from the sequence: ", num_count);
    while (count <= num_count) {
        if (scanf("%lf", &current_num) != 1) { //If user inputs non number than Error will be given
            printf("Invalid input.\n");
            return 1;
        }
        if ((c = getchar()) == '\n') {    //If user wants to input less than count of numbers in sequence then they can press enter to signal they are done inputting
            break;
        }
        bin[(int)(current_num * NUM_BINS)]++;
        count++;
    }
    if (count < num_count) {
        printf("%d numbers are required, but only %d were provided.\n", num_count, count); //If user inputs fewer doubles than originally specified
        return 1;
    }


    // Calculate the expected counts for each bin assuming an exponential distribution with mean of 1
    double expected[NUM_BINS];
    for (int z = 0; z < NUM_BINS; z++) {
        expected[z] = num_count * calculate_cdf((z+1.0)/NUM_BINS) - num_count * calculate_cdf(z/NUM_BINS);
    }


    // Calculate the chi-squared statistic
    double chi2 = 0.0;
    for (int x = 0; x < NUM_BINS; x++) {
        chi2 += pow((double)bin[x] - expected[x], 2) / expected[x];
    }

    printf("\n");


    // Print statement based on chi-squared value
    if (chi2 <= 14.684) {
        printf("The sequence is consistent with an exponential distribution with mean of 1 (D = %.2f).\n", chi2);
    }
    else if (chi2 > 14.684 && chi2 <= 21.666){
        printf("The sequence is suspicious (D = %.2f).\n", chi2);
    }
    else if (chi2 > 21.666){
        printf("The sequence is unlikely to come from an exponential distribution with mean of 1 (D = %.2f).\n", chi2);
    }
}


//Definitions
double calculate_cdf(double x) {
    return 1 - exp(-x);
}