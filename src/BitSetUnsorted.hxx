#pragma once
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include "_main.hxx"

using std::forward_iterator_tag;
using std::pair;
using std::vector;
using std::find_if;
using std::swap;




template <class T=NONE>
class BitsetUnsorted {
  vector<uint16_t> highs;
  vector2d<pair<uint16_t, T>> lows;
  int N;


  // Cute helpers.
  private:
  static uint16_t hi(int id) { return id >> 16; }
  static uint16_t lo(int id) { return id & 0xFF; }
  static int full(uint16_t hi, uint16_t lo) { return (hi<<16) | lo; }

  protected:
  auto getEntry(int i, int j) {
      const auto& hi = highs[i];
      const auto& lo = lows[i][j];
      return make_pair(full(hi, lo.first), lo.second);
  }

  auto lookup(int id) const {
    int i = findEqIndex(highs, hi(id));
    int j = i<0? -1 : findIfEqIndex(lows, [&](const auto& e) { return e.first==lo(id); });
    return make_pair(i, j);
  }


  // Get values.
  public:
  class Iterator {
    using iterator = Iterator;
    public:
    int i, j;

    public:
    using iterator_category = forward_iterator_tag;
    using difference_type   = int;
    using value_type = pair<int, T>;
    using reference  = value_type;
    using pointer    = const value_type*;

    public:
    Iterator(int i, int j) : i(i), j(j) {}
    reference operator*() const { return getEntry(i, j); }
    iterator& operator++() {
      if (lows[i].size() >= ++j) { ++i; j = 0; }
      return *this;
    }
    iterator operator++(int) {
      iterator it = *this; ++(*this);
      return it;
    }
    friend bool operator==(const iterator& l, const iterator& r) {
      return l.i==r.i && l.j==r.j;
    }
    friend bool operator!=(const iterator& l, const iterator& r) {
      return l.i!=r.i && l.j!=r.j;
    }
  };


  // Read as iterable.
  public:
  auto entries() const {
    auto b = Iterator(0, 0);
    auto e = Iterator(highs.size(), 0);
    return makeIter(b, e);
  }
  auto keys()    const { return transform(entries(), [](const auto& e) { return e.first; }); }
  auto values()  const { return transform(entries(), [](const auto& e) { return e.second; }); }


  // Read operations.
  public:
  size_t size() const { return N; }

  bool has(int id) const {
    auto [i, j] = lookup(id);
    return i>=0 && j>=0;
  }

  T get(int id) const {
    auto [i, j] = lookup(id);
    return i<0 || j<0? T() : lows[i][j].second;
  }

  // Write operations
  public:
  void clear() {
    highs.clear();
    lows.clear();
  }

  void set(int id, T v) {
    auto [i, j] = lookup(id);
    if (i<0 || j<0) return;
    lows[i][j].second = v;
  }

  void add(int id, T v=T()) {
    auto [i, j] = lookup(id);
    if (i>=0 && j>=0) return;
    if (i<0) highs.push_back(hi(id));
    lows.push_back(make_pair(lo(id), v));
  }

  void remove(int id) {
    auto [i, j] = lookup(id);
    if (i<0 || j<0) return;
    swap(lows[i].back(), lows[i][j]);
    lows[i].pop_back();
    if (!lows[i].empty()) break;
    eraseIndex(lows, i);
    eraseIndex(highs, i);
  }
};
