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
float runReadSnapTemporal(const char* type, G& x, const string& data, size_t edges, int repeat) {
  float t = measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporalW(x, s, edges); });
  }, repeat);
  print(x); printf(" [%09.3f ms] readSnapTemporal [%s]\n", t, type);
  return t;
}


template <class G, class H>
float runTransposeWithDegree(const char* type, const G& x, H& xt, int repeat) {
  float t = measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegreeW(xt, x); });
  }, repeat);
  print(xt); printf(" [%09.3f ms] transposeWithDegree [%s]\n", t, type);
  return t;
}


void runExpt(const string& data, int repeat) {
  UnorderedDiGraph<>     x1;
  LazyUnorderedDiGraph<> x2;
  OrderedDiGraph<>       x3;
  LazyOrderedDiGraph<>   x4;
  UnorderedDiGraph<int, int>     xt1;
  LazyUnorderedDiGraph<int, int> xt2;
  OrderedDiGraph<int, int>       xt3;
  LazyOrderedDiGraph<int, int>   xt4;

  size_t edges = countLines(data);
  printf("Temporal edges: %zu\n", edges);

  // Read temporal graph.
  runReadSnapTemporal("unordered",      x1, data, edges, repeat);
  runReadSnapTemporal("lazy-unordered", x2, data, edges, repeat);
  runReadSnapTemporal("ordered",        x3, data, edges, repeat);
  runReadSnapTemporal("lazy-ordered",   x4, data, edges, repeat);

  // Transpose graph.
  runTransposeWithDegree("unordered",      x1, xt1, repeat);
  runTransposeWithDegree("lazy-unordered", x2, xt2, repeat);
  runTransposeWithDegree("ordered",        x1, xt1, repeat);
  runTransposeWithDegree("lazy-ordered",   x2, xt2, repeat);
}


int main(int argc, char **argv) {
  char *file = argv[1];
  int repeat = argc>2? stoi(argv[2]) : 5;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runExpt(d, repeat);
  printf("\n");
  return 0;
}
