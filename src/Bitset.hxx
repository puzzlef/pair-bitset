#pragma once
#include "_main.hxx"
#include <utility>
#include <vector>
#include <algorithm>

using std::pair;
using std::vector;
using std::lower_bound;
using std::merge;
using std::min;




template <class T=NONE>
class Bitset {
  int  sorted;
  vector<pair<int, T>> data;
  const bool unsortedFirst;
  const int  unsortedLimit;

  // Cute helpers
  private:
  inline int unsorted() const {
    return data.size() - sorted;
  }

  inline int lookupSorted(int id) const {
    auto fl = [](const auto& e, int id) { return e.first <  id; };
    auto fe = [](const auto& e, int id) { return e.first == id; };
    return lowerBoundEqIndex(sliceIter(data, 0, sorted), id, fl, fe);
  }

  inline int lookupUnsorted(int id) const {
    auto fe = [&](const auto& e) { return e.first == id; };
    int   i = findIfIndex(sliceIter(data, sorted), fe);
    return i==unsorted()? -1 : sorted+i;
  }

  inline int lookupSortedFirst(int id) const {
    int i = lookupSorted(id);
    return i>=0? i : lookupUnsorted(id);
  }

  inline int lookupUnsortedFirst(int id) const {
    int i = lookupUnsorted(id);
    return i>=0? i : lookupSorted(id);
  }

  auto lookup(int id) const {
    if (unsortedFirst) return lookupUnsortedFirst(id);
    return lookupSortedFirst(id);
  }

  void mergeUnsorted() {
    auto ib = data.begin();
    auto im = data.begin() + sorted();
    auto ie = data.end();
    sort(im, ie);
    merge(ib, im, im, ie, ib);
    sorted = data.size();
  }

  void mergeAuto() {
    if (unsorted() <= unsortedLimit) return;
    mergeUnsorted();
  }

  void removeAtSorted(int i) {
    eraseIndex(data, i);
  }

  void removeAtUnsorted(int i) {
    int l = data.size()-1;
    sorted = min(sorted, i);
    swap(data[i], data[l]);
    data.pop_back();
  }

  void removeAt(int i) {
    int UB = data.size() - unsortedLimit;
    if (i<UB) removeAtSorted(i);
    else removeAtUnsorted(i);
  }

  // Read as iterable.
  public:
  auto entries() const { return transformIter(data, [](const auto& e) { return e; }); }
  auto keys()    const { return transformIter(data, [](const auto& e) { return e.first; }); }
  auto values()  const { return transformIter(data, [](const auto& e) { return e.second; }); }

  // Read operations.
  public:
  size_t size()      const { return data.size(); }
  bool   has(int id) const { return lookup(id) != -1; }
  T      get(int id) const { int i = lookup(id); return i>=0? data[i].second : T(); }

  // Write operations
  public:
  void clear() {
    data.clear();
  }

  void set(int id, T v) {
    int i = lookup(id);
    if (i<0) return;
    data[i].second = v;
  }

  void add(int id, T v=T()) {
    auto i = lookup(id);
    if (i>=0) return;
    data.push_back({id, v});
    mergeAuto();
  }

  void remove(int id) {
    int i = lookup(id);
    if (i<0) return;
    removeAt(i);
  }

  // Lifetime operations
  public:
  Bitset(bool unsortedFirst, int unsortedLimit)
  : sorted(), data(), unsortedFirst(unsortedFirst), unsortedLimit(unsortedLimit) {}
};
