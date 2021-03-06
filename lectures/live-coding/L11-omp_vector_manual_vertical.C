// ECE 459 Live Coding example
// Lecture 11
//  start 4 threads,
//    each thread across 1/4 of the array
//    and then increments 1000 times
// /opt/oracle/solarisstudio12.3/bin/CC -std=c++11 -O3 L11-omp_vector_manual_vertical.C   -o L11-omp_vector_manual_vertical -lpthread

#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <string.h>

#define NUM_THREADS (4)
#define ARRAY_LENGTH (1024*1024)
#define ARRAY_OFFSET (ARRAY_LENGTH / NUM_THREADS)

double * vector;

void setup(int id) {
  int i;
  for (i = id * ARRAY_OFFSET; i < (id+1) * ARRAY_OFFSET; i++) {
    for (int j = 0; j < 1000; j++) {
      vector[i] += 1.0;
    }
  }
}

int main() {
  vector = (double *) malloc(sizeof(double) * 1024 * 1024);
  memset(vector, 0, sizeof(double) * 1024 * 1024);
  std::thread * t = new std::thread[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++)
    t[i] = std::thread(setup, i);
  for (int i = 0; i < NUM_THREADS; i++)
    t[i].join();
  printf("vector[0] = %f\n", vector[0]);
}

