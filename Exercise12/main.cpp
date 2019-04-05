#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <stddef.h>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

int main( int argc, char *argv[] ) {
   MPI_Init( &argc, &argv );
   int size, rank, rc, tag = 1;
   char node_name[MPI_MAX_PROCESSOR_NAME];
   int len;
   MPI_Status Stat;
   MPI_Comm_size( MPI_COMM_WORLD, &size );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   memset(node_name,0,10);
   MPI_Get_processor_name(node_name, &len);
   printf( "(INFO) I am MPI[%d of %d]\n", rank, size);
   int mySpecialInt;
   int needForSwapFlag = 0;
   int whoToSwap1;
   int whoToSwap2;
   int neutralWhoToSwap = 999;

   if (rank == 0) {
     int myIntegerArr[4] = {12,14,16,18};
     int myTargets[4] = {1,2,3,4};
     
     
     rc = MPI_Send(&myIntegerArr[0], 1, MPI_INT, 1, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&myIntegerArr[1], 1, MPI_INT, 2, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&myIntegerArr[2], 1, MPI_INT, 3, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&myIntegerArr[3], 1, MPI_INT, 4, tag, MPI_COMM_WORLD);
     cout << "START STEP:From rank 0, we sent 12 to rank 1,14 to rank 2,16 to rank3,18 to rank4" << endl;
     
     int pickedNode1 = 1;
     int pickedNode2 = 2;
     int whoToSwap1 = 2;
     int whoToSwap2 = 1;
     
     needForSwapFlag = 0; //means don't swap it
     rc = MPI_Send(&needForSwapFlag, 1, MPI_INT, 3, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&needForSwapFlag, 1, MPI_INT, 4, tag, MPI_COMM_WORLD);
     needForSwapFlag = 1; //means swap it
     rc = MPI_Send(&needForSwapFlag, 1, MPI_INT, pickedNode1, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&needForSwapFlag, 1, MPI_INT, pickedNode2, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&whoToSwap1, 1, MPI_INT, pickedNode1, tag, MPI_COMM_WORLD);
     rc = MPI_Send(&whoToSwap2, 1, MPI_INT, pickedNode2, tag, MPI_COMM_WORLD);
     needForSwapFlag = 0;

   }
   if (rank == 1) {     
     rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     cout << "From rank 1, we received " << mySpecialInt << endl;
     rc = MPI_Recv(&needForSwapFlag, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     if(needForSwapFlag == 1){
       rc = MPI_Recv(&neutralWhoToSwap, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 1 will swap its number: " << mySpecialInt << " with Rank " << neutralWhoToSwap << endl;
       rc = MPI_Send(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD);
       rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 1 says this is my final number after swap: " << mySpecialInt << endl; 
     }
   }
   if(rank == 2) {
     rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     cout << "From rank 2, we received " << mySpecialInt << endl;
     rc = MPI_Recv(&needForSwapFlag, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     if(needForSwapFlag == 1){
       rc = MPI_Recv(&neutralWhoToSwap, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 2 will swap its number: " << mySpecialInt << " with Rank " << neutralWhoToSwap << endl;
       rc = MPI_Send(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD);
       rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 2 says this is my final number after swap: " << mySpecialInt << endl; 
     }
   }
   if(rank == 3) {
     rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     cout << "From rank 3, we received " << mySpecialInt << endl;
     rc = MPI_Recv(&needForSwapFlag, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     if(needForSwapFlag == 1){
       rc = MPI_Recv(&neutralWhoToSwap, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 3 will swap its number: " << mySpecialInt << " with Rank " << neutralWhoToSwap << endl;
       rc = MPI_Send(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD);
       rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 3 says this is my final number after swap: " << mySpecialInt << endl;
     }
   }
   if(rank == 4) {
     rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     cout << "From rank 4, we received " << mySpecialInt << endl;
     rc = MPI_Recv(&needForSwapFlag, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
     if(needForSwapFlag == 1){
       rc = MPI_Recv(&neutralWhoToSwap, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 4 will swap its number: " << mySpecialInt << " with Rank " << neutralWhoToSwap << endl;
       rc = MPI_Send(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD);
       rc = MPI_Recv(&mySpecialInt, 1, MPI_INT, neutralWhoToSwap, tag, MPI_COMM_WORLD, &Stat);
       cout << "Rank 4 says this is my final number after swap: " << mySpecialInt << endl;
     }
   }
   
   
   MPI_Finalize();
   return 0;
}
