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
float runReadSnapTemporal(const char* type, G& x, const string& data, int edges, int repeat) {
  float t = measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporal(x, s, edges); });
  }, repeat);
  print(x); printf(" [%09.3f ms] readSnapTemporal [%s]\n", t, type);
  return t;
}

template <class G, class H>
float runTransposeWithDegree(const char* type, const G& x, H& xt, int repeat) {
  float t = measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegree(xt, x); });
  }, repeat);
  print(xt); printf(" [%09.3f ms] transposeWithDegree [%s]\n", t, type);
  return t;
}



void runExpt(const string& data, int repeat) {
  int edges = countLines(data);
  printf("Temporal edges: %d\n", edges);
  DiGraphFull<> x1;
  DiGraphPartial<> x2;
  DiGraphFull<int> xt1;
  DiGraphPartial<int> xt2;

  // Read temporal graph.
  runReadSnapTemporal("full", x1, data, edges, repeat);
  runReadSnapTemporal("partial", x2, data, edges, repeat);

  // Transpose graph.
  runTransposeWithDegree("full", x1, xt1, repeat);
  runTransposeWithDegree("partial", x2, xt2, repeat);
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
