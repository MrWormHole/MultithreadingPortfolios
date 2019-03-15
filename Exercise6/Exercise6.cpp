#include "omp.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int r[6] = {2,3,5,8,13,21};
float res = 0.0f;

float vec[4][2] = {3.0f,4.0f,
                   6.0f,8.0f,
                   5.0f,12.0f,
                   7.0f,24.0f};

void part1(int* vars) {
#pragma omp parallel for private(res) schedule(static)
 for(int i = 0; i < 6; i++) {
  res = M_PI * vars[i] * vars[i];
  printf("Circle with radius %d has area of %f\n",vars[i],res);
 }
}

void part2(float vecs[4][2],int shiftValue) {
  float temp[4][2];
 for(int i = 0; i < 4; i++) {
  temp = vecs
#pragma omp parallel for 
  for(int j = 0; j < 2; j++) {
   vecs[i][j] += shiftValue;
  }
 }
 for (int m = 0; m < 4; m++) {
  cout << vec[i][0] << " " << vec[i][1] << endl;
 }
}

int main() {
 //part1(r);
 //part2(vec,1);
 return 0;
}

