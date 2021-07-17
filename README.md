Testing the effectiveness of **sorted** vs **unsorted** list of integers for BitSet.

This experiment was for comparing performance between:
1. Read graph edges to **sorted bitset** based DiGraph & transpose.
2. Read graph edges to **unsorted bitset** based DiGraph & transpose.

Each approach was attempted on a number of temporal graphs, running each with
multiple batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run 5
times for each approach to get a good time measure. **Transpose** of DiGraph
based on **sorted bitset** is clearly **faster** than the *unsorted* one.
However, with **reading graph edges** there is no clear winner (sometimes
*sorted* is *faster* especially for large graphs, and sometimes *unsorted*).
Maybe when new edges have many duplicates, **inserts are less**, and hence
sorted version is faster (since sorted bitset has slow insert time).

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection]. This experiment was done with
guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt

# (SHORTENED)
# ...
#
# Using graph sx-stackoverflow ...
# Temporal edges: 63497051
# order: 2601977 size: 36233450 {}
#
# # Batch size 1e+3
# [00003.650 ms] readSnapTemporal [sorted]
# [00002.289 ms] readSnapTemporal [unsorted]
# [05808.473 ms] transposeWithDegree [sorted]
# [16766.326 ms] transposeWithDegree [unsorted]
#
# # Batch size 5e+3
# [00009.728 ms] readSnapTemporal [sorted]
# [00010.450 ms] readSnapTemporal [unsorted]
# [05893.706 ms] transposeWithDegree [sorted]
# [16913.642 ms] transposeWithDegree [unsorted]
#
# # Batch size 1e+4
# [00019.183 ms] readSnapTemporal [sorted]
# [00018.723 ms] readSnapTemporal [unsorted]
# [05894.552 ms] transposeWithDegree [sorted]
# [16950.788 ms] transposeWithDegree [unsorted]
#
# # Batch size 5e+4
# [00075.656 ms] readSnapTemporal [sorted]
# [00080.469 ms] readSnapTemporal [unsorted]
# [05909.356 ms] transposeWithDegree [sorted]
# [16974.218 ms] transposeWithDegree [unsorted]
#
# # Batch size 1e+5
# [00137.122 ms] readSnapTemporal [sorted]
# [00156.376 ms] readSnapTemporal [unsorted]
# [05853.389 ms] transposeWithDegree [sorted]
# [16997.236 ms] transposeWithDegree [unsorted]
#
# # Batch size 5e+5
# [00655.838 ms] readSnapTemporal [sorted]
# [00779.563 ms] readSnapTemporal [unsorted]
# [06244.627 ms] transposeWithDegree [sorted]
# [17584.221 ms] transposeWithDegree [unsorted]
#
# # Batch size 1e+6
# [01332.689 ms] readSnapTemporal [sorted]
# [01597.662 ms] readSnapTemporal [unsorted]
# [06975.711 ms] transposeWithDegree [sorted]
# [18913.694 ms] transposeWithDegree [unsorted]
#
# # Batch size 5e+6
# [06263.879 ms] readSnapTemporal [sorted]
# [07612.980 ms] readSnapTemporal [unsorted]
# [07603.789 ms] transposeWithDegree [sorted]
# [20472.597 ms] transposeWithDegree [unsorted]
#
# # Batch size 1e+7
# [10948.173 ms] readSnapTemporal [sorted]
# [13276.812 ms] readSnapTemporal [unsorted]
# [08421.293 ms] transposeWithDegree [sorted]
# [23075.482 ms] transposeWithDegree [unsorted]
#
# # Batch size 5e+7
# [29084.017 ms] readSnapTemporal [sorted]
# [35400.736 ms] readSnapTemporal [unsorted]
# [11465.749 ms] transposeWithDegree [sorted]
# [34081.889 ms] transposeWithDegree [unsorted]
```

[![](https://i.imgur.com/AO60Lp2.gif)][sheets]
[![](https://i.imgur.com/PfnYurJ.gif)][sheets]
[![](https://i.imgur.com/yOU9KUs.gif)][sheets]
[![](https://i.imgur.com/FOCek4N.gif)][sheets]
[![](https://i.imgur.com/FNjzMwG.gif)][sheets]
[![](https://i.imgur.com/yjf6gHQ.gif)][sheets]
[![](https://i.imgur.com/0oJxvcN.gif)][sheets]
[![](https://i.imgur.com/aCxMYZ5.gif)][sheets]
[![](https://i.imgur.com/vTGHuYE.gif)][sheets]
[![](https://i.imgur.com/Ka37H7J.gif)][sheets]
[![](https://i.imgur.com/PMP8x2V.gif)][sheets]
[![](https://i.imgur.com/xTkdVrU.gif)][sheets]
[![](https://i.imgur.com/L9IsuTD.gif)][sheets]
[![](https://i.imgur.com/sxNrmL2.gif)][sheets]

<br>
<br>


## References

- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/DuJu78s.jpg)](https://www.youtube.com/watch?v=2k_ihEEZG-o)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[charts]: https://photos.app.goo.gl/c2ivFPbEXdw6ZFaM7
[sheets]: https://docs.google.com/spreadsheets/d/1AB23nO5K71-TWe7aY6cf5Rte7jfLhfITPFBnRB_jVzM/edit?usp=sharing
