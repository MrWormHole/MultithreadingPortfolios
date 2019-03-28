#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <stddef.h>
#include <string.h>
#include <iostream>

using namespace std;


typedef struct infoAboutNodes_s {
char hostname[MPI_MAX_PROCESSOR_NAME];
int core_count = 1;
int rank;
} infoAboutNodes;

int main( int argc, char *argv[] ) {
   MPI_Init( &argc, &argv );
   int size, rank, source, rc, tag = 1;
   char node_name[MPI_MAX_PROCESSOR_NAME];
   int len;
   MPI_Status Stat;
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   memset(node_name,0,10);
   MPI_Get_processor_name(node_name, &len);
   printf( "(INFO) I am MPI[%d of %d]\n", rank, size);
   
   const int count = 3;
   int blockLengths[3] = {10,10,10};
   MPI_Datatype types[3] = {MPI_CHAR,MPI_INT,MPI_INT};
   MPI_Datatype mpi_infoAboutNodes;
   MPI_Aint offsets[3];
   offsets[0] = offsetof(infoAboutNodes,hostname);
   offsets[1] = offsetof(infoAboutNodes,core_count);
   offsets[2] = offsetof(infoAboutNodes,rank);
   MPI_Type_create_struct(count,blockLengths,offsets,types,&mpi_infoAboutNodes);
   MPI_Type_commit(&mpi_infoAboutNodes);

   if (rank == 0) {
     source= 0;
     infoAboutNodes sample1;
	   sample1.rank = 0;

     strncpy(sample1.hostname, node_name, len);
     for(int i = 1; i < size; i++){
       rc = MPI_Send(&sample1, 1, mpi_infoAboutNodes, i, tag, MPI_COMM_WORLD);
     }
     
     rc = MPI_Recv(&sample1, 1, mpi_infoAboutNodes, source, tag, MPI_COMM_WORLD, &Stat);
	 cout << "Rank 0 sent compound data type to all Ranks" << endl;
   }
   else if(rank == 1){
     source = rank;
     infoAboutNodes sample2;
     rc = MPI_Recv (&sample2, 1, mpi_infoAboutNodes, source, tag, MPI_COMM_WORLD, &Stat);
	   sample2.rank = rank;
     strncpy(sample2.hostname,node_name,len);
     rc = MPI_Send (&sample2, 1, mpi_infoAboutNodes, 0,  tag, MPI_COMM_WORLD);
	 cout << "Rank " << rank << " received compound data type to Rank 0 and also sent a compound data to Rank 0" << endl;
   }
   
   
   MPI_Type_free(&mpi_infoAboutNodes);
   MPI_Finalize();
	 return 0;
}
