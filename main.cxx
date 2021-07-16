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




void runExptConfig(const string& data, int repeat, int edges, int mode, int limit) {
  DiGraph<> x(mode, limit);
  DiGraph<int> xt(mode, limit);

  // Read temporal graph.
  float t1 = measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporal(x, s, edges); });
  }, repeat);
  print(x); printf(" [%09.3f ms; mode=%d; limit=%d] readSnapTemporal\n", t1, mode, limit);

  // Transpose graph.
  float t2 = measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegree(xt, x); });
  }, repeat);
  print(xt); printf(" [%09.3f ms; mode=%d; limit=%d] transposeWithDegree\n", t2, mode, limit);
}


void runExpt(const string& data, int repeat) {
  int edges = countLines(data);
  int limitBegin = 1, limitEnd = 10000;
  printf("Temporal edges: %d\n", edges);
  for (int P=1; P<=limitEnd; P*=10) {
    for (int limit=P; limit<P*10; limit+=P) {
      if (limit > limitEnd) break;
      for (int mode=0; mode<8; mode++)
        runExptConfig(data, repeat, edges, mode, limit);
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
