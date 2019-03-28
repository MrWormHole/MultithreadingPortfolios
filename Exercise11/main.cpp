#include "mpi.h"
#include "omp.h"
#include <iostream>
#include <string.h>

using namespace std;

int main( int argc, char *argv[] ) {
   MPI_Init( &argc, &argv );
   int size, rank;
   char node_name[MPI_MAX_PROCESSOR_NAME];
   int len;
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   memset(node_name,0,10);
   MPI_Get_processor_name(node_name, &len);
   
//#pragma omp parallel
   //printf("I am %s, node %d of %d and this is processor %d of %d\n",node_name,rank,size,omp_get_thread_num(),omp_get_max_threads());
   
   int arr[10] = {1,2,3,4,5,6,7,8,9,10};
   //simple array operation with parallelism
   int result = 0;
   int x = 0;
   int c = 10;
#pragma omp parallel for private(x) shared(c)
  for(int n = 0; n < c; n++ ) {
    x = 4;
    result += arr[n] + x;
  }
  //result has to be 95
   
   if (rank == 0) {
    MPI_Send(&result, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    printf("I am %s, node of %d of %d and this is processor %d of %d and the result message is %d\n",node_name,rank,size,omp_get_thread_num(),omp_get_max_threads() ,result);
  } else {
    int buffer;
    MPI_Status status;
    MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_INT, &buffer);
    if (buffer == 1) {
        printf("I am %s, node of %d of %d and this is processor %d of %d and the result message is %d\n",node_name,rank,size,omp_get_thread_num(),omp_get_max_threads() ,result);
        MPI_Recv(&result, buffer, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (rank + 1 != size) {
            MPI_Send(&result, 1, MPI_INT, ++rank, 0, MPI_COMM_WORLD);
        }
    };
  };
   
   MPI_Finalize();
	 return 0;
}
