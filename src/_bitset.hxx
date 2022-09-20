#pragma once
#include <utility>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_map>
#include "_algorithm.hxx"
#include "_ctypes.hxx"
#include "_iterator.hxx"
#include "_utility.hxx"

using std::pair;
using std::vector;
using std::unordered_map;
using std::out_of_range;
using std::make_pair;
using std::back_inserter;
using std::move;
using std::find_if;
using std::lower_bound;
using std::inplace_merge;
using std::sort;




// BITSET-*
// --------
// Helps create bitsets.

#ifndef BITSET_TYPES
#define BITSET_TYPES(K, V, buf, data) \
  using key_type    = K; \
  using value_type  = V; \
  using pair_type   = pair<K, V>; \
  using buffer_type = buf; \
  using iterator       = decltype(data.begin()); \
  using const_iterator = decltype(data.cbegin());
#endif


#ifndef BITSET_ITERATOR
#define BITSET_ITERATOR_RANGE(K, V, db, de) \
  ITERABLE_ITERATOR(inline, noexcept, db, de)
#define BITSET_CITERATOR_RANGE(K, V, db, de) \
  ITERABLE_CITERATOR(inline, noexcept, db, de)

#define BITSET_ITERATOR(K, V, data) \
  BITSET_ITERATOR_RANGE(K, V, data.begin(), data.end())
#define BITSET_CITERATOR(K, V, data) \
  BITSET_CITERATOR_RANGE(K, V, data.begin(), data.end())
#endif


#ifndef BITSET_SIZE
#define BITSET_SIZE(K, V)  \
  inline size_t size() const noexcept { return distance(begin(), end()); }
#define BITSET_EMPTY(K, V) \
  inline bool empty()  const noexcept { return size() == 0; }
#endif


#ifndef BITSET_FCOMPARE
#define BITSET_FCOMPARE(fn, op) \
  auto fn = [](const auto& p, const auto& q) { return p.first op q.first; };
#define BITSET_FCOMPARES(fl, fe) \
  BITSET_FCOMPARE(fl, <) \
  BITSET_FCOMPARE(fe, ==)
#endif


#ifndef BITSET_FIND
#define BITSET_FIND(K, V) \
  inline auto find(const K& k)        noexcept { return locate_match(k); } \
  inline auto cfind(const K& k) const noexcept { return locate_match(k); } \
  inline auto find(const K& k)  const noexcept { return cfind(k); }

#define BITSET_FINDAT_USING(K, V, ffind, f0, f1) \
  inline size_t findAt(const K& k) noexcept { \
    auto   it =  ffind(k); \
    return it == end()? size_t(-1) : it - begin(); \
  }
#define BITSET_FINDAT(K, V) \
  BITSET_FINDAT_USING(K, V, find,  inline, noexcept) \
  BITSET_FINDAT_USING(K, V, cfind, inline, const noexcept) \
  BITSET_FINDAT_USING(K, V, cfind, inline, const noexcept)
#endif


#ifndef BITSET_ENTRIES
#define BITSET_ENTRIES(K, V) \
  /* dont change the keys! */ \
  inline auto values() noexcept { \
    return static_transform_iterable(begin(), end(), PairSecond<K, V>()); \
  } \
  inline auto pairs() noexcept { \
    return iterable(begin(), end()); \
  } \
  inline auto ckeys() const noexcept { \
    return static_transform_iterable(begin(), end(), ConstPairFirst<K, V>()); \
  } \
  inline auto cvalues() const noexcept { \
    return static_transform_iterable(begin(), end(), ConstPairSecond<K, V>()); \
  } \
  inline auto cpairs() const noexcept { \
    return iterable(begin(), end()); \
  } \
  inline auto keys()   const noexcept { return ckeys(); } \
  inline auto values() const noexcept { return cvalues(); } \
  inline auto pairs()  const noexcept { return cpairs(); }
#endif


#ifndef BITSET_FOREACH
#define BITSET_FOREACH_KEY_USING(K, V, db, de, pname, f0, f1) \
  template <class F> \
  f0 void pname##forEachKey(F fn) f1 { \
    for (auto it=db; it!=de; ++it) \
      fn((*it).first); \
  }
#define BITSET_FOREACH_VALUE_USING(K, V, db, de, pname, f0, f1) \
  template <class F> \
  f0 void pname##forEachValue(F fn) f1 { \
    for (auto it=db; it!=de; ++it) \
      fn((*it).second); \
  }
#define BITSET_FOREACH_PAIR_USING(K, V, db, de, pname, f0, f1) \
  template <class F> \
  f0 void pname##forEachPair(F fn) f1 { \
    for (auto it=db; it!=de; ++it) \
      fn(*it); \
  }
#define BITSET_FOREACH_USING(K, V, db, de, pname, f0, f1) \
  template <class F> \
  f0 void pname##forEach(F fn) f1 { \
    for (auto it=db; it!=de; ++it) \
      fn((*it).first, (*it).second); \
  }

#define BITSET_FOREACH(K, V) \
  /* dont change the keys! */ \
  BITSET_FOREACH_VALUE_USING(K, V, begin(), end(),, inline,) \
  BITSET_FOREACH_PAIR_USING (K, V, begin(), end(),, inline,) \
  BITSET_FOREACH_USING      (K, V, begin(), end(),, inline,) \
  BITSET_FOREACH_KEY_USING  (K, V, begin(), end(), c, inline, const) \
  BITSET_FOREACH_VALUE_USING(K, V, begin(), end(), c, inline, const) \
  BITSET_FOREACH_PAIR_USING (K, V, begin(), end(), c, inline, const) \
  BITSET_FOREACH_USING      (K, V, begin(), end(), c, inline, const) \
  template <class F> \
  inline void forEachKey(F fn)   const { cforEachKey(fn); } \
  template <class F> \
  inline void forEachValue(F fn) const { cforEachValue(fn); } \
  template <class F> \
  inline void forEachPair(F fn)  const { cforEachPair(fn); } \
  template <class F> \
  inline void forEach(F fn)      const { cforEach(fn); }
#endif


#ifndef BITSET_AT
#define BITSET_HAS(K, V) \
  inline bool has(const K& k) const noexcept { \
    return locate_match(k) != end(); \
  }

#define BITSET_GET(K, V) \
  inline V get(const K& k) const noexcept { \
    auto it = locate_match(k); \
    return it == end()? V() : (*it).second; \
  }

#define BITSET_SET(K, V) \
  inline bool set(const K& k, const V& v) noexcept { \
    auto it = locate_match(k); \
    if (it == end()) return false; \
    (*it).second = v; \
    return true; \
  }

#define BITSET_SUBSCRIPT(K, V) \
  inline V& operator[](const K& k) noexcept { \
    auto it = locate_match(k); \
    return (*it).second; \
  } \
  inline const V& operator[](const K& k) const noexcept { \
    auto it = locate_match(k); \
    return (*it).second; \
  }

#define BITSET_AT(K, V) \
  inline V& at(const K& k) { \
    auto it = locate_match(k); \
    if (it == end()) throw out_of_range("bitset key not present"); \
    return (*it).second; \
  } \
  inline const V& at(const K& k) const { \
    auto it = locate_match(k); \
    if (it == end()) throw out_of_range("bitset key not present"); \
    return (*it).second; \
  }
#endif


#ifndef BITSET_CORRECT
#define BITSET_CORRECT(K, V) \
  inline bool correct(vector<typename buffer_type>& buf) { \
    return false; \
  }
#endif


#ifndef BITSET_ADD_UNCHECKED
#define BITSET_ADD_UNCHECKED(K, V) \
  inline bool addUnchecked(const K& k, const V& v=V()) { \
    return add(k, v); \
  }
#endif


#ifndef BITSET_FILTER_IF
#define BITSET_FILTER_IF_USING(K, V, data, name, fname) \
  template <class F> \
  inline void filterIf##name(F fn) { \
    data.resize(pairs_filter_if##fname(begin(), end(), fn)); \
  }

#define BITSET_FILTER_IF(K, V, data) \
  BITSET_FILTER_IF_USING(K, V, data,,) \
  BITSET_FILTER_IF_USING(K, V, data, Key, _key) \
  BITSET_FILTER_IF_USING(K, V, data, Value, _value)
#endif




// UNORDERED-BITSET
// ----------------
// An integer set that constantly checks duplicates.
// It maintains keys in insertion order.

#define UNORDERED_BITSET_LOCATE(K, V, f0, f1) \
  f0 auto locate_match(const K& k) f1 { \
    auto fe = [&](const pair<K, V>& p) { return p.first == k; }; \
    return find_if(begin(), end(), fe); \
  }


template <bool ORD, class ID, class IK>
auto unordered_bitset_remove_batch(ID db, ID de, IK kb, IK ke, size_t kn) {
  auto fu = [&](const auto& d) { return find_value(kb, ke, d.first) != ke; };
  auto fo = [&](const auto& d) { return lower_find(kb, ke, d.first) != ke; };
  if (!ORD || kn < linearSearchSize(*kb)) return unordered_reject_limited_if(db, de, kn, fu);
  return unordered_reject_limited_if(db, de, kn, fo);
}

template <bool ORD, class ID, class IP, class IA>
auto unordered_bitset_add_batch(ID db, ID de, IP pb, IP pe, size_t pn, IA ab, vector<bool>& buf) {
  BITSET_FCOMPARES(fl, fe)
  if (buf.size() < pn) buf.resize(pn);
  fill(buf.begin(), buf.begin() + pn, false);
  if (pn < linearSearchSize(*pb)) includes_each_value(db, de, pb, pe, buf, fe);
  else includes_each_value_ordered(db, de, pb, pe, buf, fl, fe);
  for (size_t i=0; i<pn; ++i, ++pb)
    if (!buf[i]) *(ab++) = *pb;
  return ab;
}


template <class K=int, class V=NONE>
class UnorderedBitset {
  // Data.
  protected:
  vector<pair<K, V>> data;

  // Types.
  public:
  BITSET_TYPES(K, V, bool, data)


  // Iterator operations.
  public:
  BITSET_ITERATOR(K, V, data)
  BITSET_CITERATOR(K, V, data)


  // Size operations.
  public:
  BITSET_SIZE(K, V)
  BITSET_EMPTY(K, V)


  // Search operations.
  protected:
  UNORDERED_BITSET_LOCATE(K, V, inline, noexcept)
  UNORDERED_BITSET_LOCATE(K, V, inline, const noexcept)
  public:
  BITSET_FIND(K, V)
  BITSET_FINDAT(K, V)


  // Access operations.
  public:
  BITSET_ENTRIES(K, V)
  BITSET_FOREACH(K, V)
  BITSET_HAS(K, V)
  BITSET_GET(K, V)
  BITSET_SET(K, V)
  BITSET_SUBSCRIPT(K, V)
  BITSET_AT(K, V)


  // Update operations.
  public:
  BITSET_CORRECT(K, V)
  BITSET_FILTER_IF(K, V, data)
  inline bool clear() noexcept {
    data.clear();
    return true;
  }

  inline bool remove(const K& k) {
    auto it = locate_match(k);
    if (it == end()) return false;
    *it = move(*(end()-1));
    data.pop_back();
    return true;
  }
  inline bool removeAt(size_t i) {
    auto it = begin() + i;
    *it = move(*(end()-1));
    data.pop_back();
    return true;
  }

  inline bool add(const K& k, const V& v=V()) {
    auto it = locate_match(k);
    if (it == end()) data.push_back({k, v});
    else (*it).second = v;
    return true;
  }
  inline bool addUnchecked(const K& k, const V& v=V()) {
    data.push_back({k, v});
    return true;
  }

  template <bool ORD, class KS>
  inline bool removeBatch(const KS& keys) {
    auto db = begin(), de = end();
    auto kb = keys.begin(), ke = keys.end(); size_t kn = keys.size();
    if (kn==0) return false;
    if (kn==1) return remove(*kb);
    auto it = unordered_bitset_remove_batch<ORD>(db, de, kb, ke, kn);
    data.erase(it, de);
    return it != de;
  }

  template <class PS, bool ORD=false>
  inline bool addBatch(const PS& pairs, vector<bool>& buf) {
    auto db = begin(), de = end();
    auto pb = pairs.begin(), pe = pairs.end(); size_t pn = pairs.size();
    if (pn==0) return false;
    if (pn==1) return add((*pb).first, (*pb).second);
    auto it = unordered_bitset_add_batch(db, de, pb, pe, pn, back_inserter(data), buf);
    return it != de;
  }
};

template <class K=int, class V=NONE>
inline auto unorderedBitset(K _k=K(), V _v=V()) {
  return UnorderedBitset<K, V>();
}




// LAZY-UNORDERED-BITSET
// ---------------------
// An integer set that checks duplicates only on correct().
// It maintains keys in insertion order.

template <class K=int, class V=NONE>
class LazyUnorderedBitset {
  // Data.
  protected:
  vector<pair<K, V>> data;
  vector<K> removed;
  size_t included;
  // included elements = data[0..included]
  // added elements    = data[included..]

  // Types.
  public:
  BITSET_TYPES(K, V, bool, data)


  // Iterator operations.
  public:
  BITSET_ITERATOR_RANGE (K, V, data.begin(), data.begin() + included)
  BITSET_CITERATOR_RANGE(K, V, data.begin(), data.begin() + included)


  // Size operations.
  public:
  BITSET_SIZE(K, V)
  BITSET_EMPTY(K, V)


  // Search operations.
  protected:
  UNORDERED_BITSET_LOCATE(K, V, inline, noexcept)
  UNORDERED_BITSET_LOCATE(K, V, inline, const noexcept)
  public:
  BITSET_FIND(K, V)
  BITSET_FINDAT(K, V)


  // Access operations.
  public:
  BITSET_ENTRIES(K, V)
  BITSET_FOREACH(K, V)
  BITSET_HAS(K, V)
  BITSET_GET(K, V)
  BITSET_SET(K, V)
  BITSET_SUBSCRIPT(K, V)
  BITSET_AT(K, V)


  // Update operations.
  public:
  inline bool correct(vector<bool>& buf) {
    auto db = begin(), de = end(), pb = de, pe = data.end(); size_t pn = data.size() - size();
    auto kb = removed.begin(), ke = removed.end(); size_t kn = removed.size();
    auto ir = unordered_bitset_remove_batch<ORD>(db, de, kb, ke, kn);
    bool wasRemoved = ir != de;
    auto ia = unordered_bitset_add_batch(db, ir, pb, pe, pn, ir, buf);
    bool wasAdded   = ia != ir;
    data.erase(ia, data.end());
    removed.clear();
    included = data.size();
    return wasRemoved || wasAdded;
  }

  BITSET_FILTER_IF(K, V, data)
  inline bool clear() noexcept {
    data.clear();
    removed.clear();
    included = 0;
    return true;
  }

  inline bool remove(const K& k) {
    removed.push_back(k);
    return true;
  }
  inline bool removeAt(size_t i) {
    removed.push_back(data[i].first);
    return true;
  }

  inline bool add(const K& k, const V& v=V()) {
    data.push_back({k, v});
    return true;
  }
  BITSET_ADD_UNCHECKED(K, V)

  template <bool ORD, class KS>
  inline bool removeBatch(const KS& keys) {
    removed.insert(removed.end(), keys.begin(), keys.end());
    return keys.size() != 0;
  }

  template <bool ORD, class PS>
  inline bool addBatch(const PS& pairs, vector<bool>& buf) {
    data.insert(data.end(), pairs.begin(), pairs.end());
    return pairs.size() != 0;
  }
};

template <class K=int, class V=NONE>
inline auto lazyUnorderedBitset(K _k=K(), V _v=V()) {
  return LazyUnorderedBitset<K, V>();
}




// ORDERED-BITSET
// --------------
// An integer set that constantly checks duplicates.
// It maintains integers in ascending value order.

#define ORDERED_BITSET_LOCATE(K, V, f0, f1) \
  f0 auto locate_spot(const K& k) f1 { \
    auto fl = [](const pair<K, V>& p, const K& k) { return p.first < k; }; \
    return lower_bound(begin(), end(), k, fl); \
  } \
  f0 auto locate_match(const K& k) f1 { \
    auto it = locate_spot(k); \
    return it == end() || (*it).first != k? end() : it; \
  }


template <bool ORD, class ID, class IK>
auto ordered_bitset_remove_batch(ID db, ID de, IK kb, IK ke, size_t kn) {
  auto fu = [&](const auto& d) { return find_value(kb, ke, d.first) != ke; };
  auto fo = [&](const auto& d) { return lower_find(kb, ke, d.first) != ke; };
  if (!ORD || kn < linearSearchSize(*kb)) return reject_limited_if(db, de, kn, fu);
  return reject_limited_if(db, de, kn, fo);
}

template <class ID, class IP, class IA>
auto ordered_bitset_add_batch(ID db, ID de, IP pb, IP pe, size_t pn, vector<bool>& buf) {
  BITSET_FCOMPARES(fl, fe)
  if (buf.size() < pn+2) buf.resize(pn+2);  // see inplace_set_union()
  return inplace_set_union(db, de, pb, pe, buf.begin(), buf.end());
}


template <class K=int, class V=NONE>
class OrderedBitset {
  // Data.
  protected:
  vector<pair<K, V>> data;

  // Types.
  public:
  BITSET_TYPES(K, V, pair<K, V>, data)


  // Iterator operations.
  public:
  BITSET_ITERATOR(K, V, data)
  BITSET_CITERATOR(K, V, data)


  // Size operations.
  public:
  BITSET_SIZE(K, V)
  BITSET_EMPTY(K, V)


  // Search operations.
  protected:
  ORDERED_BITSET_LOCATE(K, V, inline, noexcept)
  ORDERED_BITSET_LOCATE(K, V, inline, const noexcept)
  public:
  BITSET_FIND(K, V)
  BITSET_FINDAT(K, V)


  // Access operations.
  public:
  BITSET_ENTRIES(K, V)
  BITSET_FOREACH(K, V)
  BITSET_HAS(K, V)
  BITSET_GET(K, V)
  BITSET_SET(K, V)
  BITSET_SUBSCRIPT(K, V)
  BITSET_AT(K, V)


  // Update operations.
  public:
  BITSET_CORRECT(K, V)
  BITSET_FILTER_IF(K, V, data)
  inline bool clear() noexcept {
    data.clear();
    return true;
  }

  inline bool remove(const K& k) {
    auto it = locate_match(k);
    if (it == end()) return false;
    data.erase(it);
    return true;
  }
  inline bool removeAt(size_t i) {
    auto it = begin() + i;
    data.erase(it);
    return true;
  }

  inline bool add(const K& k, const V& v=V()) {
    auto it = locate_spot(k);
    if (it != end() && (*it).first == k) (*it).second = v;
    else data.insert(it, {k, v});
    return true;
  }
  inline bool addUnchecked(const K& k, const V& v=V()) {
    auto it = locate_spot(k);
    data.insert(it, {k, v});
    return true;
  }

  template <bool ORD, class KS>
  inline bool removeBatch(const KS& keys) {
    auto db = begin(), de = end();
    auto kb = keys.begin(), ke = keys.end(); size_t kn = keys.size();
    if (kn==0) return false;
    if (kn==1) return remove(*kb);
    auto it = ordered_bitset_remove_batch<ORD>(db, de, kb, ke, kn);
    data.erase(it, de);
    return it != de;
  }

  template <bool ORD, class PS>
  inline bool addBatch(const PS& pairs, vector<pair<K, V>>& buf) {
    auto db = begin(), de = end(), it = de;
    auto pb = pairs.begin(), pe = pairs.end(); size_t pn = pairs.size();
    auto fp = [&](const auto& p) { if (add(p.first, p.second)) ++it; };
    if (pn==0) return false;
    if (pn==1 || !ORD) { for_each(pb, pe, fp); return it != de; }
    data.resize(data.size() + pn);
    it = ordered_bitset_add_batch(db, de, pb, pe, pn, buf);
    data.erase(it, data.end());
    return it != de;
  }
};

template <class K=int, class V=NONE>
inline auto orderedBitset(K _k=K(), V _v=V()) {
  return OrderedBitset<K, V>();
}




// LAZY-ORDERED-BITSET
// -------------------
// An integer set that checks duplicates only on correct().
// It maintains keys in ascending value order.

template <class K=int, class V=NONE>
class LazyOrderedBitset {
  // Data.
  protected:
  vector<pair<K, V>> data;
  vector<K> removed;
  size_t included;
  // included elements = data[0..included]
  // added elements    = data[included..]

  // Types.
  public:
  BITSET_TYPES(K, V, pair<K, V>, data)


  // Iterator operations.
  public:
  BITSET_ITERATOR_RANGE (K, V, data.begin(), data.begin() + included)
  BITSET_CITERATOR_RANGE(K, V, data.begin(), data.begin() + included)


  // Size operations.
  public:
  BITSET_SIZE(K, V)
  BITSET_EMPTY(K, V)


  // Search operations.
  protected:
  ORDERED_BITSET_LOCATE(K, V, inline, noexcept)
  ORDERED_BITSET_LOCATE(K, V, inline, const noexcept)
  public:
  BITSET_FIND(K, V)
  BITSET_FINDAT(K, V)


  // Access operations.
  public:
  BITSET_ENTRIES(K, V)
  BITSET_FOREACH(K, V)
  BITSET_HAS(K, V)
  BITSET_GET(K, V)
  BITSET_SET(K, V)
  BITSET_SUBSCRIPT(K, V)
  BITSET_AT(K, V)


  // Update operations.
  public:
  inline bool correct(vector<pair<K, V>>& buf) {
    auto db = begin(), de = end(), pb = de, pe = data.end(); size_t pn = data.size() - size();
    auto kb = removed.begin(), ke = removed.end(); size_t kn = removed.size();
    auto ir = ordered_bitset_remove_batch<ORD>(db, de, kb, ke, kn);
    bool wasRemoved = ir != de;
    auto ia = ordered_bitset_add_batch(db, ir, pb, pe, pn, buf);
    bool wasAdded   = ia != ir;
    data.erase(ia, data.end());
    removed.clear();
    included = data.size();
    return wasRemoved || wasAdded;
  }

  BITSET_FILTER_IF(K, V, data)
  inline bool clear() noexcept {
    data.clear();
    removed.clear();
    included = 0;
    return true;
  }

  inline bool remove(const K& k) {
    removed.push_back(k);
    return true;
  }
  inline bool removeAt(size_t i) {
    removed.push_back(data[i].first);
    return true;
  }

  inline bool add(const K& k, const V& v=V()) {
    data.push_back({k, v});
    return true;
  }
  BITSET_ADD_UNCHECKED(K, V)

  template <bool ORD, class KS>
  inline bool removeBatch(const KS& keys) {
    removed.insert(removed.end(), keys.begin(), keys.end());
    return keys.size() != 0;
  }

  template <bool ORD, class PS>
  inline bool addBatch(const PS& pairs, vector<pair<K, V>>& buf) {
    data.insert(data.end(), pairs.begin(), pairs.end());
    return pairs.size() != 0;
  }
};

template <class K=int, class V=NONE>
inline auto lazyOrderedBitset(K _k=K(), V _v=V()) {
  return LazyOrderedBitset<K, V>();
}




// RETYPE
// ------

template <class K, class V, class KA=K, class VA=V>
constexpr auto retype(const UnorderedBitset<K, V>& x, KA _k=KA(), VA _v=VA()) {
  return UnorderedBitset<KA, VA>();
}
template <class K, class V, class KA=K, class VA=V>
constexpr auto retype(const LazyUnorderedBitset<K, V>& x, KA _k=KA(), VA _v=VA()) {
  return LazyUnorderedBitset<KA, VA>();
}
template <class K, class V, class KA=K, class VA=V>
constexpr auto retype(const OrderedBitset<K, V>& x, KA _k=KA(), VA _v=VA()) {
  return OrderedBitset<KA, VA>();
}
template <class K, class V, class KA=K, class VA=V>
constexpr auto retype(const LazyOrderedBitset<K, V>& x, KA _k=KA(), VA _v=VA()) {
  return LazyOrderedBitset<KA, VA>();
}




// WRITE
// -----

template <class B>
void writeBitset(ostream& a, const B& x) {
  a << "{\n";
  x.forEach([&](const auto& k, const auto& v) {
    a << "  " << k << ": " << v << "\n";
  });
  a << "}";
}

template <class K, class V>
inline void write(ostream& a, const UnorderedBitset<K, V>& x)     { writeBitset(a, x); }
template <class K, class V>
inline void write(ostream& a, const LazyUnorderedBitset<K, V>& x) { writeBitset(a, x); }
template <class K, class V>
inline void write(ostream& a, const OrderedBitset<K, V>& x)       { writeBitset(a, x); }
template <class K, class V>
inline void write(ostream& a, const LazyOrderedBitset<K, V>& x)   { writeBitset(a, x); }

template <class K, class V>
inline ostream& operator<<(ostream& a, const UnorderedBitset<K, V>& x)     { write(a, x); return a; }
template <class K, class V>
inline ostream& operator<<(ostream& a, const LazyUnorderedBitset<K, V>& x) { write(a, x); return a; }
template <class K, class V>
inline ostream& operator<<(ostream& a, const OrderedBitset<K, V>& x)       { write(a, x); return a; }
template <class K, class V>
inline ostream& operator<<(ostream& a, const LazyOrderedBitset<K, V>& x)   { write(a, x); return a; }




// COPY
// ----

template <class B, class C>
inline void copyBitsetW(B& a, const C& x) {
  a.clear();
  x.forEach([&](const auto& k, const auto& v) { a.addUnchecked(k, v); });
}

template <class B, class K, class V>
inline void copyW(B& a, const UnorderedBitset<K, V>& x)     { copyBitsetW(a, x); }
template <class B, class K, class V>
inline void copyW(B& a, const LazyUnorderedBitset<K, V>& x) { copyBitsetW(a, x); }
template <class B, class K, class V>
inline void copyW(B& a, const OrderedBitset<K, V>& x)       { copyBitsetW(a, x); }
template <class B, class K, class V>
inline void copyW(B& a, const LazyOrderedBitset<K, V>& x)   { copyBitsetW(a, x); }
