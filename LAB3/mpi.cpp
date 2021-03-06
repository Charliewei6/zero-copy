/** derived from */
  

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include "mpi.h"  

// how many threads to run
#define NUM_THREADS 3

/**
* Output:
* Arrays match.
* real  0m0.150s
* user  0m0.117s
* sys 0m0.0329s
*/


void createData(int const num_rows, int const num_cols, float* const a, float* const b,
                      float* const c, float* const ref);
void checkSol(int const num_rows, int const num_cols, float const* const a, float const* const b);

/**
 * optimize this code
 */
void add(float* const a, float* const b, float* const c, int const num_rows, int const num_cols)
{
    // omp_set_num_threads(NUM_THREADS);
    // #pragma omp parallel
    // {
      //#pragma omp for schedule(static)
      for(int row = 0; row < num_rows; row++) {
       for(int col = 0; col < num_cols; col++) {
           int i = col + row * num_cols;
           c[i] = a[i] + b[i];
       }
      }
   // }
    
}

int main(int argc ,char** argv)
{
    float *a, *b, *c, *sol;

    int    const NUM_ROWS = 2048;
    int    const NUM_COLS = 2048;
    size_t const N_BYTES = NUM_ROWS * NUM_COLS * sizeof(float);
    a   = (float*)malloc(N_BYTES);
    b   = (float*)malloc(N_BYTES);
    c   = (float*)malloc(N_BYTES);
    sol = (float*)malloc(N_BYTES);
    int my_rank = 0, comm_sz = 0;
     MPI_Init(&argc ,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
        clock_t start = clock();

    createData(NUM_ROWS, NUM_COLS, a, b, c, sol);

    // c = a + b
    add(a, b, c, NUM_ROWS, NUM_COLS);

    checkSol(NUM_ROWS, NUM_COLS, c, sol);

    free(a); 
    free(b); 
    free(c); 
    free(sol);
    MPI_Finalize();
    double time = (double)(clock() - start);
    std::cout << std:: endl << "OpenMP Running Time is " << time << " milli second"<< std::endl;
    return 0;
}

void createData(int const num_rows, int const num_cols, float* const a, float* const b, float* const c, float* const ref)
{
    int row, col;

    srand((unsigned)time(NULL));

    for(int row = 0; row < num_rows; row++) {
       for(int col = 0; col < num_cols; col++) {
           int i = col + row * num_cols;
           a[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
           b[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
           c[i] = 0.0f;
           ref[i] = a[i] + b[i];
        }
    }
}

void checkSol(int const num_rows, int const num_cols, float const* const a, float const* const b)
{
    int const N = num_rows * num_cols;

    int i;
    int different = 0;

    for(int i = 0; i < N; i++) {
        different = (a[i] != b[i]);
        if(different) break;
    }

    if(different)
        printf("Arrays do not match.\n");
    else
        printf("Arrays match.\n");
}
