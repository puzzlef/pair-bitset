#include <random>
#include <cstdio>
#include <iostream>
#include "src/main.hxx"

using namespace std;




void runComparision(const char *file) {
  random_device dev;
  default_random_engine rnd(dev());
  DiGraphVector<> x;
  DiGraphUmap<> y;
  DiGraphVector<int> xt;
  DiGraphUmap<int> yt;

  // Read mtx using DiGraph with "vector" edges
  float t1 = measureDuration([&] { readMtx(x, file); });
  print(x); printf(" [%09.3f ms] readMtx(DiGraphVector)\n", t1);

  // Read mtx using DiGraph with "unordered_map" edges
  float t2 = measureDuration([&] { readMtx(y, file); });
  print(y); printf(" [%09.3f ms] readMtx(DiGraphUmap)\n", t2);

  // Update DiGraph with "vector" edges
  int span = int(1.5 * x.span()), updates = int(0.5 * x.size());
  float t5 = measureDuration([&] {
    for (int i=0; i<updates; i++)
      addRandomEdge(x, rnd, span);
  });
  print(x); printf(" [%09.3f ms] addRandomEdge(DiGraphVector)\n", t5);

  // Update DiGraph with "unordered_map" edges
  float t6 = measureDuration([&] {
    for (int i=0; i<updates; i++)
      addRandomEdge(y, rnd, span);
  });
  print(y); printf(" [%09.3f ms] addRandomEdge(DiGraphUmap)\n", t6);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  runComparision(file);
  printf("\n");
  return 0;
}
