#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <utility>
#include <algorithm>
#include "src/main.hxx"

using namespace std;




void runExptConfig(const string& data, int repeat, int edges, bool unsortedFirst, int unsortedLimit) {
  DiGraph<> x(unsortedFirst, unsortedLimit);
  DiGraph<int> xt(unsortedFirst, unsortedLimit);

  // Read temporal graph.
  float t1 = measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporal(x, s, edges); });
  }, repeat);
  print(x); printf(" [%09.3f ms; unsorted-first=%d; unsorted-limit=%d] readSnapTemporal\n", t1, unsortedFirst, unsortedLimit);

  // Transpose graph.
  float t2 = measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegree(xt, x); });
  }, repeat);
  print(xt); printf(" [%09.3f ms; unsorted-first=%d; unsorted-limit=%d] transposeWithDegree\n", t2, unsortedFirst, unsortedLimit);
}


void runExpt(const string& data, int repeat) {
  int edges = countLines(data);
  int limitBegin = 1, limitEnd = 10000;
  printf("Temporal edges: %d\n", edges);
  for (int P=1; P<=limitEnd; P*=10) {
    for (int limit=P; limit<P*10; limit+=P) {
      if (limit > limitEnd) break;
      runExptConfig(data, repeat, edges, false, limit);
      runExptConfig(data, repeat, edges, true,  limit);
    }
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 1;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runExpt(d, repeat);
  printf("\n");
  return 0;
}
