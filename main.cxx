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




template <class G>
float runReadSnapTemporal(G& x, const string& data, int batch) {
  int repeat = 5;
  return measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporal(x, s, batch); });
  }, repeat);
}


template <class G, class H>
float runTransposeWithDegree(H& xt, const G& x) {
  int repeat = 5;
  return measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegree(xt, x); });
  }, repeat);
}


void runExptBatch(const string& data, bool show, int batch, int switchPoint) {
  DiGraph<> x(switchPoint);
  DiGraph<int> xt(switchPoint);

  // Read temporal edges to switched BitSet based DiGraph.
  float t1 = runReadSnapTemporal(x, data, batch);
  print(x); printf(" [%09.3f ms; switch-point=%d] readSnapTemporal\n", switchPoint, t1);

  // Transpose switched BitSet based DiGraph.
  float t2 = runTransposeWithDegree(xt, x);
  print(xt); printf(" [%09.3f ms; switch-point=%d] transposeWithDegree\n", switchPoint, t2);
}


void runExpt(const string& data, bool show) {
  int M = countLines(data);
  printf("Temporal edges: %d\n\n", M);
  runExptBatch(data, show, M, 0);
  for (int switchPoint=1, i=0; switchPoint<M; switchPoint*=i&1? 2:5, i++)
    runExptBatch(data, show, M, switchPoint);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runExpt(d, show);
  printf("\n");
  return 0;
}
