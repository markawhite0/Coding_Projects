//enee140_gen_rnd.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define RND_MAX RAND_MAX


unsigned X;     //Current value of RNG
unsigned m;     //Modulus exponent: M = 2^m
unsigned A;     //Multiplier
unsigned B;     //Increment


//Function to scanf user input for menu selection and algorithm selection
int get_num(int max);

//Function to populate seed
void seed_rnd(unsigned seed, int algorithm);

//Function to generate random number using linear congruential(LC) method
unsigned gen_rnd();

//Function to print numbers until the user specified number for menu option 2
int print_num(int num_amount);

//Function to generate random numbers that doesn't go past limit specified by user
unsigned gen_rnd_limit(unsigned max_number);

//Function to print RND_MAX based on selected algorithm
void rnd_max(int algorithm);

//Function to generate random numbers between a specified min and max range
int gen_rnd_range(int min_gen, int max_gen);

//Function to generate random float point numbers between a specified min and max range
float gen_rnd_float(float min_gen, float max_gen);

//Function to generate random numbers that has a mean that equals what the user specified
float gen_rnd_exp(float mean);


int main() {

    int algorithm,menu;
    int num_amount, max_number;
    unsigned seed;
    signed s_max_number, s_min_number;
    float f_max_number, f_min_number, mean;

    // Print the main menu and get the user's choice
    printf("\nWelcome to the ENEE140 pseudo-random number generator!\n\n");
    printf("1: Print RND_MAX\n");
    printf("2: Generate uniformly-distributed positive integers\n");
    printf("3: Generate uniformly-distributed positive integers, up to a given limit\n");
    printf("4: Generate uniformly-distributed integers, from a given range\n");
    printf("5: Generate uniformly-distributed floats, from a given range\n");
    printf("6: Generate exponentially-distributed floats\n");

    //Obtain user inputs for menu and algorithm
    menu = get_num(6);
    printf("\nSelect the algorithm to use.");
    algorithm = get_num(3);

    //Obtain user input for seed and calls the seed_rnd function
    printf("\nSelect the seed for the random number generator:");
    scanf("%u", &seed);
    printf("\n");
    seed_rnd(seed, algorithm);

    //If-else statements for menu selections
    while (menu == 1){
        rnd_max(algorithm);
        menu = get_num(6);
    }
    if (menu == 2) {
        printf("How many numbers should I generate:");
        scanf("%d", &num_amount);
        print_num(num_amount);
    }
    else if (menu == 3) {
        printf("How many numbers should I generate:");
        scanf("%d", &num_amount);
        printf("Enter the maximum number to generate:");
        scanf("%d", &max_number);
        for (int i = 0; i < num_amount; i++) {
            printf("%u ", gen_rnd_limit(max_number));
        }
        printf("\n");
    }
    else if (menu == 4) {
        printf("How many numbers should I generate:");
        scanf("%d", &num_amount);
        printf("Enter the minimum number to generate:");
        scanf("%d", &s_min_number);
        printf("Enter the maximum number to generate:");
        scanf("%d", &s_max_number);
        for (int i = 0; i < num_amount; i++) {
            printf("%d ", gen_rnd_range(s_min_number, s_max_number));
        }
        printf("\n");
    }
    else if (menu == 5) {
        printf("How many numbers should I generate:");
        scanf("%d", &num_amount);
        printf("Enter the minimum number to generate:");
        scanf("%f", &f_min_number);
        printf("Enter the maximum number to generate:");
        scanf("%f", &f_max_number);
        for (int i = 0; i < num_amount; i++) {
            printf("%.2f ", gen_rnd_float(f_min_number, f_max_number));
        }
        printf("\n");
        }
    else if (menu == 6) {
        printf("How many numbers should I generate:");
        scanf("%d", &num_amount);
        printf("Enter the mean of the distribution:");
        scanf("%f", &mean);
        while (mean < 0) {
            printf("Error: the mean must be a positive number.\n");
            printf("Enter the mean of the distribution:");
            scanf("%f", &mean);
        }
        for (int i = 0; i < num_amount; i++) {
            printf("%.2f ", gen_rnd_exp(mean));
        }
    }
}


//DEFINITIONS
void seed_rnd(unsigned seed, int algorithm){
    if(algorithm == 1){
        A = 214013;
        B = 2531011;
        m = 32;
    }
    else if(algorithm == 2){
        A = 1103515245;
        B = 12345;
        m = 32;
    }
    else if(algorithm == 3){
        A = 1103515245;
        B = 12345;
        m = 31;
    }
    X = seed;
}


unsigned gen_rnd(){
    X = (A * X + B) % (unsigned long)pow(2, m); //LC method formula to generate evenly distributed random numbers
    return X;
}


int get_num(int max) {
    int x;
    int a = 0;

    printf("\nEnter your choice (1-%d):", max);
    scanf("%d", &x);

    while (!(x >= 1 && x <= max)) {
        printf("Sorry, that is not a valid option");
        printf("\nEnter your choice (1-%d):", max);
        scanf("%d", &x);
        a++;
        if (a == 2) {
            printf("You have entered 3 invalid options. Goodbye!\n");
            exit(0);
        }
    }
    return x;
}


int print_num(int num_amount) {

    for (int i = 1; i <= num_amount; i++) {
        printf("%u ", gen_rnd());
        if (i == num_amount) {     //Continues to print random numbers until it reaches the amount of numbers that the user asked for
            printf("\n");
            exit(0);
        }
    }
}


unsigned gen_rnd_limit(unsigned max_number){
    unsigned int limit_num;

    do {
        limit_num = gen_rnd();
    } while (limit_num >= (unsigned int)(-1) / max_number * max_number);
    return limit_num % max_number;
}


void rnd_max(int algorithm){
    unsigned rnd_print;

    if(algorithm == 1){
        m = 32;
    }
    else if(algorithm == 2){
        m = 32;
    }
    else if(algorithm == 3){
        m = 31;
    }
    rnd_print = (unsigned)pow(2, m) - 1; //Formula to obtain RND_MAX based on algorithm selection
    printf("RND_MAX = %u", rnd_print);
}


int gen_rnd_range(int min_gen, int max_gen){

    if(min_gen > max_gen){
        return 0;
    }
    int range = max_gen - min_gen + 1;
    int number = gen_rnd() % range;
    return number + min_gen;
}


float gen_rnd_float(float min_gen, float max_gen){
    if(min_gen > max_gen){              //If min_gen > max_gen then program returns 0.0
        return 0.0f;
    }
    float range = max_gen - min_gen;    //Obtain the range of numbers needed from user input
    if (range > RND_MAX){
        return 0.0f;
    }
    float random_float = ((float)gen_rnd_range(0, RND_MAX)) / RND_MAX;  //Feed input into gen_rnd_range function
    return random_float * range + min_gen;  //Transform output back to caller
}


float gen_rnd_exp(float mean){
    float i = gen_rnd_float(0, 1);
    float epsilon = 1e-7;   //A small value to add to 'i' so that the case of the function taking the log of 0 is minimal
    while (i == 0) {
        i = gen_rnd_float(0, 1);    //If i == 0 then random number will generate again
    }
    return -mean * log(i + epsilon);  //Transform output back to caller
}

