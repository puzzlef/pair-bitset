#pragma once
#include "_main.hxx"
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>

using std::pair;
using std::vector;
using std::back_inserter;
using std::lower_bound;
using std::find_if;
using std::merge;
using std::inplace_merge;
using std::copy;
using std::min;




template <class T=NONE>
class Bitset {
  int sorted;
  vector<pair<int, T>>  data;
  vector<pair<int, T>> *temp;
  int mode, limit;

  // Cute helpers
  private:
  inline int  mergeMode()     const { return mode >> 1; }
  inline bool unsortedFirst() const { return mode & 1; }
  inline int  unsorted() const { return data.size() - sorted; }

  inline auto cbegin()   const { return data.begin(); }
  inline auto cmiddle()  const { return data.begin() + sorted; }
  inline auto cend()     const { return data.end(); }
  inline auto begin()  { return data.begin(); }
  inline auto middle() { return data.begin() + sorted; }
  inline auto end()    { return data.end(); }
  inline auto rbegin()  { return data.rbegin(); }
  inline auto rmiddle() { return data.rbegin() + unsorted(); }
  inline auto rend()    { return data.rend(); }

  inline int lookupSorted(int id) const {
    auto fl = [](const auto& e, int id) { return e.first <  id; };
    auto fe = [](const auto& e, int id) { return e.first == id; };
    auto it = lower_bound(cbegin(), cmiddle(), id, fl);
    return it==cend() || (*it).first!=id? -1 : it-cbegin();
  }

  inline int lookupUnsorted(int id) const {
    auto fe = [&](const auto& e) { return e.first == id; };
    auto it = find_if(cmiddle(), cend(), fe);
    return it==cend()? -1 : it-cbegin();
  }

  inline int lookupSortedFirst(int id) const {
    int i = lookupSorted(id);
    return i>=0? i : lookupUnsorted(id);
  }

  inline int lookupUnsortedFirst(int id) const {
    int i = lookupUnsorted(id);
    return i>=0? i : lookupSorted(id);
  }

  inline int lookup(int id) const {
    if (unsortedFirst()) return lookupUnsortedFirst(id);
    return lookupSortedFirst(id);
  }

  inline void mergeWithSort() {
    auto fl = [](const auto& e, const auto& f) { return e.first < f.first; };
    sort(begin(), end(), fl);
  }

  inline void mergeWithInplace() {
    auto fl = [](const auto& e, const auto& f) { return e.first < f.first; };
    sort(middle(), end(), fl);
    inplace_merge(begin(), middle(), end(), fl);
  }

  inline void mergeWithSortedSpace() {
    auto fl = [](const auto& e, const auto& f) { return e.first < f.first; };
    sort(middle(), end(), fl);
    (*temp).clear();
    copy(cbegin(), cmiddle(), back_inserter((*temp)));
    merge((*temp).begin(), (*temp).end(), middle(), end(), begin(), fl);
  }

  inline void mergeWithUnsortedSpace() {
    auto fl = [](const auto& e, const auto& f) { return e.first < f.first; };
    auto fg = [](const auto& e, const auto& f) { return e.first > f.first; };
    sort(middle(), end(), fl);
    (*temp).clear();
    copy(cmiddle(), cend(), back_inserter((*temp)));
    merge((*temp).rbegin(), (*temp).rend(), rmiddle(), rend(), rbegin(), fg);
  }

  inline void mergeAuto() {
    if (unsorted() <= limit) return;
    switch (mergeMode()) {
      default:
      case 0: mergeWithSort(); break;
      case 1: mergeWithInplace(); break;
      case 2: mergeWithSortedSpace(); break;
      case 3: mergeWithUnsortedSpace(); break;
    }
    sorted = data.size();
  }

  inline void removeAtSorted(int i) {
    eraseIndex(data, i);
  }

  inline void removeAtUnsorted(int i) {
    int l = data.size()-1;
    sorted = min(sorted, i);
    swap(data[i], data[l]);
    data.pop_back();
  }

  inline void removeAt(int i) {
    int UB = data.size() - limit;
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
  Bitset(int mode, int limit, vector<pair<int, T>> *temp) :
  sorted(), data(), temp(temp), mode(mode), limit(limit) {}
};
