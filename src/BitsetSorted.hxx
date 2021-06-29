#pragma once
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include "_main.hxx"

using std::pair;
using std::vector;
using std::forward_iterator_tag;
using std::make_pair;
using std::find_if;
using std::swap;




template <class T=NONE>
class BitsetSorted {
  protected:
  vector<uint16_t> highs;
  vector2d<pair<uint16_t, T>> lows;
  int N;


  // Cute helpers.
  protected:
  static uint16_t hi(int id) { return id >> 16; }
  static uint16_t lo(int id) { return id & 0xFF; }
  static int full(uint16_t hi, uint16_t lo) { return (hi<<16) | lo; }

  protected:
  auto getEntry(int i, int j) const {
      const auto& hi = highs[i];
      const auto& lo = lows[i][j];
      return make_pair(full(hi, lo.first), lo.second);
  }

  auto where(int id) const {
    int i = lowerBoundIndex(highs, hi(id));
    if (i>=highs.size() || highs[i]!=hi(id)) return make_pair(i, 0);
    int j = lowerBoundIndex(lows[i], id, [&](const auto& e, int id) { return e.first < lo(id); });
    return make_pair(i, j);
  }

  auto lookup(int id) const {
    int i = lowerBoundEqIndex(highs, hi(id));
    if (i<0) return make_pair(-1, -1);
    int j = lowerBoundIndex(lows[i], id, [&](const auto& e, int id) { return e.first < lo(id); });
    return j>=lows[i].size() || lows[i][j].first!=lo(id)? make_pair(i, -1) : make_pair(i, j);
  }


  // Get values.
  public:
  class Iterator {
    using iterator = Iterator;
    using super    = BitsetSorted<T>;
    const super& x;
    public:
    int i, j;

    public:
    using iterator_category = forward_iterator_tag;
    using difference_type   = int;
    using value_type = pair<int, T>;
    using reference  = value_type;
    using pointer    = const value_type*;

    public:
    Iterator(const super& x, int i, int j) : x(x), i(i), j(j) {}
    reference operator*() const { return x.getEntry(i, j); }
    iterator& operator++() {
      if (++j >= x.lows[i].size()) { ++i; j = 0; }
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
    auto b = Iterator(*this, 0, 0);
    auto e = Iterator(*this, highs.size(), 0);
    return makeIter(b, e);
  }
  auto keys()   const { return transformIter(entries(), [](const auto& e) { return e.first; }); }
  auto values() const { return transformIter(entries(), [](const auto& e) { return e.second; }); }


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
    N = 0;
  }

  void set(int id, T v) {
    auto [i, j] = lookup(id);
    if (i<0 || j<0) return;
    lows[i][j].second = v;
  }

  void add(int id, T v=T()) {
    auto [i, j] = where(id);
    if (i>=highs.size() || highs[i]!=hi(id)) {
      insertIndex(highs, i, hi(id));
      insertIndex(lows, i, {});
    }
    if (j>=lows[i].size() || lows[i][j].first!=lo(id)) {
      insertIndex(lows[i], j, make_pair(lo(id), v)); N++;
    }
  }

  void remove(int id) {
    auto [i, j] = lookup(id);
    if (i<0 || j<0) return;
    eraseIndex(lows[i], j); N--;
    if (!lows[i].empty()) return;
    eraseIndex(lows, i);
    eraseIndex(highs, i);
  }
};
