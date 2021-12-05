#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

void createData(int const num_rows, int const num_cols, int* const a, int* const b, int* const sum);
void findPrime(int const num_rows, int const num_cols, int const* const sum);
int main()
{
    int *a, *b, *sum;
    int    const NUM_ROWS = 100;
    int    const NUM_COLS = 100;
    size_t const N_BYTES = NUM_ROWS * NUM_COLS * sizeof(int);
    a   = (int*)malloc(N_BYTES);
    b   = (int*)malloc(N_BYTES);
    sum = (int*)malloc(N_BYTES);

    clock_t start = clock();
    createData(NUM_ROWS, NUM_COLS, a, b, sum);

    findPrime(NUM_ROWS, NUM_COLS, sum);
    free(a); 
    free(b); 
    free(sum); 
    double time = (double)(clock() - start);
    std::cout << std:: endl << "Base line Running Time is " << time << " milli second"<< std::endl;
    return 0;
}

void createData(int const num_rows, int const num_cols, int* const a, int* const b, int* const sum)
{
    int row, col;

    srand((unsigned)time(NULL));

    for(int row = 0; row < num_rows; row++) {
       for(int col = 0; col < num_cols; col++) {
           int i = col + row * num_cols;
           a[i] = i;
           b[i] = i+1;
           sum[i] = a[i] + b[i];
        }
    }
}
void findPrime(int const num_rows, int const num_cols, int const* const sum){
    int const N = num_rows * num_cols;

    int num = 0;

    for(int k = 0; k < N; k++) {
        int i, n;
        bool isPrime = true;
        n = sum[k];

        // 0 and 1 are not prime numbers
        if (n == 0 || n == 1) {
            isPrime = false;
        }
        else {
            for (i = 2; i <= n / 2; ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
        }
        if (isPrime)
           num++;


    }
    printf("total number is: %d.\n",num);
}