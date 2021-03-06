#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

void part1() {
//this will print number of cores times in your computer
#pragma omp parallel
cout << omp_get_thread_num() << endl;
}

void part2() {
int arr[10] = {1,2,3,4,5,6,7,8,9,10};
//simple array operation with parallelism
#pragma omp parallel for
 for(int n = 0; n < 10; n++ ) {
  arr[n] = 2 * arr[n];
  cout << arr[n] << "\n";
 }
}

int main (void)
{
//part1();
//part2();
return 0;
}