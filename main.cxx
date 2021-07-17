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




template <size_t C=128>
void runExptConfig(const string& data, int repeat, int edges) {
  DiGraph<NONE, NONE, C> x;
  DiGraph<int, NONE, C> xt;

  // Read temporal graph.
  float t1 = measureDurationMarked([&](auto mark) {
    x.clear();
    stringstream s(data);
    mark([&] { readSnapTemporal(x, s, edges); });
  }, repeat);
  print(x); printf(" [%09.3f ms; buffer=%d] readSnapTemporal\n", t1, C);

  // Transpose graph.
  float t2 = measureDurationMarked([&](auto mark) {
    xt.clear();
    mark([&] { transposeWithDegree(xt, x); });
  }, repeat);
  print(xt); printf(" [%09.3f ms; buffer=%d] transposeWithDegree\n", t2, C);
}


void runExpt(const string& data, int repeat) {
  int edges = countLines(data);
  int limitBegin = 1, limitEnd = 10000;
  printf("Temporal edges: %d\n", edges);
  runExptConfig<1>(data, repeat, edges);
  runExptConfig<2>(data, repeat, edges);
  runExptConfig<4>(data, repeat, edges);
  runExptConfig<8>(data, repeat, edges);
  runExptConfig<16>(data, repeat, edges);
  runExptConfig<32>(data, repeat, edges);
  runExptConfig<64>(data, repeat, edges);
  runExptConfig<128>(data, repeat, edges);
  runExptConfig<256>(data, repeat, edges);
  runExptConfig<512>(data, repeat, edges);
  runExptConfig<1024>(data, repeat, edges);
  runExptConfig<2048>(data, repeat, edges);
  runExptConfig<4096>(data, repeat, edges);
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
