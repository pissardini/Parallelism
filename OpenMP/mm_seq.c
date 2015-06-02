/******************************************************************
* FILE: mm_seq.c
* DESCRIPTION: Sequential Matrix Multiplication.
* AUTHOR: R.S. Pissardini
******************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

int main(int argc, char **argv) {

    long **a, **b, **c;
    int N = 100;

    struct timeval start, end; //Variables of measurement of time

    if (argc == 2) {
      N = atoi (argv[1]); //maximum N is 951.
      assert (N > 0);
    }

    int i,j,k,mul=5;
    int col_sum = N * (N-1) / 2; //change to "long" for N>951

    a = (long **)malloc (N * sizeof(long *));
    b = (long **)malloc (N * sizeof(long *));
    c = (long **)malloc (N * sizeof(long *));
    for (i=0; i<N; i++) {
      a[i] = (long *)malloc (N * sizeof(long));
      b[i] = (long *)malloc (N * sizeof(long));
      c[i] = (long *)malloc (N * sizeof(long));
    }

    gettimeofday(&start, NULL); 

    for (i=0; i<N; i++)
      for (j=0; j<N; j++) {
          a[i][j] = i*mul;
          b[i][j] = i;
          c[i][j] = 0;
      }

    printf ("Matrix generation finished.\n");

    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	       for (k=0; k<N; k++)
	           c[i][j] += a[i][k] * b[k][j];

    printf ("Multiplication finished.\n");

    gettimeofday(&end, NULL);

    double delta = ((end.tv_sec  - start.tv_sec) * 1000000u +
         end.tv_usec - start.tv_usec) / 1.e6; 

    printf("%.16g\n", delta); //show time processment


    for (i=0; i<N; i++)
      for (j=0; j<N; j++)
	        assert (c[i][j] == i*mul* col_sum);

    printf ("Test finished.\n");
}
