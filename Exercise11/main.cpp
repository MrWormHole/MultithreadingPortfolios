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
   
   #pragma omp parallel
   printf("I am %s, node %d of %d and this is processor %d of %d\n",node_name,rank,size,omp_get_thread_num(),omp_get_max_threads()); 
   
   MPI_Finalize();
	 return 0;
}
