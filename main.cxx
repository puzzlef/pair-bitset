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


void runExptBatch(const string& data, bool show, int batch) {
  DiGraph<> x1;
  DiGraph<> x2;
  DiGraph<int> xt1;
  DiGraph<int> xt2;

  // Read temporal edges to sorted BitSet based DiGraph.
  float t1 = runReadSnapTemporal(x1, data, batch);
  print(x1); printf(" [%09.3f ms] readSnapTemporal [sorted]\n", t1);

  // Read temporal edges to unsorted BitSet based DiGraph.
  float t2 = runReadSnapTemporal(x2, data, batch);
  print(x2); printf(" [%09.3f ms] readSnapTemporal [unsorted]\n", t2);

  // Transpose sorted BitSet based DiGraph.
  float t3 = runTransposeWithDegree(xt1, x1);
  print(xt1); printf(" [%09.3f ms] transposeWithDegree [sorted]\n", t3);

  // Transpose unsorted BitSet based DiGraph.
  float t4 = runTransposeWithDegree(xt2, x2);
  print(xt2); printf(" [%09.3f ms] transposeWithDegree [unsorted]\n", t4);
}


void runExpt(const string& data, bool show) {
  int M = countLines(data);
  printf("Temporal edges: %d\n\n", M);
  for (int batch=1000, i=0; batch<M; batch*=i&1? 2:5, i++)
    runExptBatch(data, show, batch);
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
