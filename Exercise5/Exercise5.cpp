#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

using namespace std;

void part1() {
 for(int i = 0; i < 1000; i++) {
  cout << i << endl;
 }
usleep(2000000);
#pragma omp parallel for
 for(int i = 0; i < 1000; i++) {
  cout << i << endl;
 }
}

int part2(int  arr[3][2]) {
 int sum = 0;
 srand(time(NULL));
 for(int i = 0; i < 3; i++) {
  for(int j = 0; j < 2; j++) {
   arr[i][j] = rand() % 6;
  }
 } 
#pragma omp parallel for collapse(2)
 for(int i = 0; i < 3; i++) {
  for(int j = 0; j < 2; j++) {
   sum += arr[i][j];
   printf("Value %d has been added from matrix entry |%d||%d|\n",arr[i][j],i,j);
   //cout << "Value " << arr[i][j] << " has been added from matrix entry " << "|" << i << "|" << "|" << j << "|" << "\n";
  }
 }
 return sum; 
}

int main() {
 //part1();
 int arr[3][2] = {0,1,
                  2,3,
                  4,5};
 cout << part2(arr) << "\n";
 return 0;
}