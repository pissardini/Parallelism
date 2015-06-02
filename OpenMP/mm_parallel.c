/******************************************************************************
* FILE: mm_parallel.c
* DESCRIPTION:Matrix Multiplication using OpenMP.
* AUTHOR: R.S.Pissardini
* Compilation: gcc mm_parallel.c -o multp -lm -fopenmp
* Execution: OMP_NUM_THREADS=<p> ./multp <n> where <p> is the number of processes
*            and <n> is the size of matrix.
******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>
#include <sys/time.h>

int main(int argc, char **argv) {
   
    long **a, **b, **c;
    int N = 100;

    if (argc == 2) {
      N = atoi (argv[1]);
      assert (N > 0);
    }
    
    int i,j,k,mul=5;
    int col_sum = N * (N-1) / 2;

    a = (long **)malloc (N * sizeof(long *));
    b = (long **)malloc (N * sizeof(long *));
    c = (long **)malloc (N * sizeof(long *));
 

    for (i=0; i<N; i++) {
	      a[i] = (long *)malloc (N * sizeof(long));
	      b[i] = (long *)malloc (N * sizeof(long));
	      c[i] = (long *)malloc (N * sizeof(long));
	    }


    double start = omp_get_wtime(); 

    /*****Parallel Region************/
    #pragma omp parallel shared (a,b,c) private (i,j,k)
    {
	    
	   #pragma omp for schedule (static)
	   for (i=0; i<N; i++)
	      for (j=0; j<N; j++) {
            a[i][j] = i*mul;
            b[i][j] = i;
            c[i][j] = 0;
	       }
	       
	   printf ("Matrix generation finished.\n");
	    
	   #pragma omp for schedule (static)

	   for (i=0; i<N; i++)
	      for (j=0; j<N; j++)
		        for (k=0; k<N; k++)
		            c[i][j] += a[i][k] * b[k][j];

	   printf ("Multiplication finished.\n");

	   #pragma omp for schedule (static)
	   for (i=0; i<N; i++)
	      for (j=0; j<N; j++)
		            assert ( c[i][j] == i*mul * col_sum);  

    } /*****End of Parallel Region **********/
    
    double end = omp_get_wtime();
    printf("%.16g (s)\n", end - start); 

  printf ("Test finished.\n");         
}

