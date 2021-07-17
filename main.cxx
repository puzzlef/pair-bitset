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




void runExptBatch(const string& data, bool show, int batch, int skip) {
  DiGraph<> x1;
  DiGraph<> x2;
  stringstream s1(data);
  stringstream s2(data);
  vector<int> ks1, ks2;
  bool read1, read2;
  float t1, t2;

  while (true) {
    t1 = measureDuration([&] { read1 = readSnapTemporal(x1, s1, batch); });
    t2 = measureDuration([&] { read2 = readSnapTemporal(x2, s2, batch); });
    print(x1); printf(" [%09.3f ms] readSnapTemporal [sorted]\n", t1);
    print(x2); printf(" [%09.3f ms] readSnapTemporal [unsorted]\n", t2);
    if (!read1 || !read2) break;
    ks1 = vertices(x1);
    ks2 = vertices(x2);
    DiGraph<int> xt1;
    DiGraph<int> xt2;
    t1 = measureDuration([&] { transposeWithDegree(xt1, x1); });
    t2 = measureDuration([&] { transposeWithDegree(xt2, x2); });
    print(x1); printf(" [%09.3f ms] transposeWithDegree [sorted]\n", t1);
    print(x2); printf(" [%09.3f ms] transposeWithDegree [unsorted]\n", t2);

    // Skip some edges (to speed up execution)
    if (skip) {
      if (!readSnapTemporal(x1, s1, skip)) break;
      if (!readSnapTemporal(x2, s2, skip)) break;
    }
  }
}


void runExpt(const string& data, bool show) {
  int M = countLines(data), steps = 100;
  printf("Temporal edges: %d\n\n", M);
  for (int batch=1000, i=0; batch<M; batch*=i&1? 2:5, i++) {
    int skip = max(M/steps - batch, 0);
    printf("# Batch size %.0e\n", (double) batch);
    runExptBatch(data, show, batch, skip);
    printf("\n");
  }
}


int main(int argc, char **argv) {
  char *file = argv[1];
  bool  show = argc > 2;
  printf("Using graph %s ...\n", file);
  string d = readFile(file);
  runExpt(d, show);
  return 0;
}
