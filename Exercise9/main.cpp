#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( int   argc, char *argv[] ) {
   int size, rank, dest, source, rc, count, tag = 1;
   time_t t;
   //
   srand((unsigned)time(&t));
   int inmsg, outmsg= 666;
   MPI_Status Stat;


   /*while(dest == source) {
     source = rand() % 11;
     dest = rand() % 11;
   }*/

   MPI_Init( &argc, &argv );
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   printf( "(INFO) I am MPI[%d of %d]\n", rank, size);

   if (rank%2 == 0) {
     dest=(rank+1)%size;
     source=(rank+1)%size;
     outmsg++;
     rc = MPI_Send(&outmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD);
     rc = MPI_Recv(&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
   }
   else {
     dest = (rank-1+size)%size;
     source = (rank-1+size)%size;
     rc = MPI_Recv (&inmsg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &Stat);
     outmsg++;
     rc = MPI_Send (&outmsg, 1, MPI_INT, dest,  tag, MPI_COMM_WORLD);
   }
    
   rc = MPI_Get_count( &Stat, MPI_INT, &count );
   printf( "Task %d: Received %d int(s) from task %d with tag %d\n And Task %d received number was %d\n", rank, count, Stat.MPI_SOURCE,Stat.MPI_TAG,rank,inmsg);
   MPI_Finalize();
	 return 0;
}
