#include <cassert>
#include <utility>
#include <vector>
#include "src/main.hxx"

using namespace std;




template <class B>
void runExpt(B& x) {
  using K = typename B::key_type;
  using V = typename B::value_type;
  using W = typename B::buffer_type;
  vector<W> buf;
  // Check if bitset if empty.
  assert(x.empty());
  assert(x.size() == 0);
  // Check add behaviour.
  for (K i=0; i<100; ++i)
    x.add(i % 10, i);
  x.correct(buf);
  assert(x.size() == 10);
  for (K i=90; i<100; ++i)
    assert(x.get(i % 10) == i);
  // Check remove behaviour.
  for (K i=0; i<100; ++i)
    x.remove((i % 10) & 0xFE);
  x.correct(buf);
  assert(x.size() == 5);
  for (K i=90; i<100; ++i)
    if (i & 1 == 1) assert(x.get(i % 10) == i);
  // Check clear behaviour.
  x.clear();
  assert(x.size() == 0);
  // Check remove + add batch behaviour.
  vector<K> removes;
  vector<pair<K, V>> adds;
  for (K i=0; i<100; ++i)
    x.add(i % 20, i);
  x.correct(buf);
  for (K i=0; i<100; ++i)
    removes.push_back((i % 20) & 0xFE);
  for (K i=0; i<100; ++i)
    adds.push_back({i % 10, i});
  removes.resize(sortedUnique(removes));
  adds.resize(sortedUnique(adds));
  x.removeBatch<true>(removes);
  x.addBatch<true>(adds, buf);
  x.correct(buf);
  assert(x.size() == 15);
  for (K i=90; i<100; ++i)
    assert(x.get(i % 10) == i);
  for (K i=91; i<100; i+=2)
    assert(x.get(i % 20) == i);
}


int main(int argc, char **argv) {
  UnorderedBitset<int, float>     x1;
  OrderedBitset<int, float>       x2;
  LazyUnorderedBitset<int, float> x3;
  LazyOrderedBitset<int, float>   x4;
  printf("Using UnorderedBitset ...\n");
  runExpt(x1); printf("Verified.\n\n");
  printf("Using OrderedBitset ...\n");
  runExpt(x2); printf("Verified.\n\n");
  printf("Using LazyUnorderedBitset ...\n");
  runExpt(x3); printf("Verified.\n\n");
  printf("Using LazyOrderedBitset ...\n");
  runExpt(x4); printf("Verified.\n\n");
  return 0;
}
