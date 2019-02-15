#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

void part1() {
//this will print number of cores
#pragma omp parallel
cout << omp_get_thread_num() << endl;
}

void part2() {
int arr[10] = {1,2,3,4,5,6,7,8,9,10};

//running count = 10
//great example
#pragma omp parallel
#pragma omp for 
 for(int n = 0; n < 10; n++ ) {
  arr[n] = 2 * arr[n];
  cout << arr[n] << "\n";
 }
}

void test() {
int temp[10] = {0};

//running count = 10 * number of cores
//not a good example
#pragma omp parallel
{
 for(int i = 0; i < 10; i++ ) {
  temp[i] = 1 + temp[i];
  cout << temp[i] << "\n";
 }
} 
}

int main (void)
{
//part1();
//part2();
//test();
return 0;
}