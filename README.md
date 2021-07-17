Comparing various **buffer sizes** for BitSet with **small vector optimization**.

**Read graph edges**, and **transpose**,  was attempted on a number of temporal
graphs, running each with multiple buffer sizes (`1`, `2`, `4`, ...`4096`).
Each buffer size was run 5 times for for both **read** and **transpose** to get
a good time measure. On average, a **buffer size** of `4` seems to give **small**
**improvement**. Any further increase in buffer size slows down performance.
This is possibly because of unnecessaryily large contiguous large memory allocation
needed by the buffer, and low cache-hit percent due to widely separated edge data
(due to the static buffer). In fact it even crashes when 26 instances of graphs
with varying buffer sizes can't all be held in memory. Hence, **small vector**
**optimization** is **not useful**, atleast when used for graphs.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection]. This experiment was done with
guidance from [Prof. Dip Sankar Banerjee] and [Prof. Kishore Kothapalli].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt
$ ./a.out ~/data/CollegeMsg.txt
$ ...

# ...
#
# Using graph /home/subhajit/data/sx-stackoverflow.txt ...
# Temporal edges: 63497051
# order: 2601977 size: 36233450 {} [92162.930 ms; buffer=1] readSnapTemporal
# order: 2601977 size: 36233450 {} [14232.156 ms; buffer=1] transposeWithDegree
# order: 2601977 size: 36233450 {} [92023.273 ms; buffer=2] readSnapTemporal
# order: 2601977 size: 36233450 {} [13923.403 ms; buffer=2] transposeWithDegree
# order: 2601977 size: 36233450 {} [91467.188 ms; buffer=4] readSnapTemporal
# order: 2601977 size: 36233450 {} [13847.361 ms; buffer=4] transposeWithDegree
# order: 2601977 size: 36233450 {} [91495.625 ms; buffer=8] readSnapTemporal
# order: 2601977 size: 36233450 {} [13677.591 ms; buffer=8] transposeWithDegree
# order: 2601977 size: 36233450 {} [90916.078 ms; buffer=16] readSnapTemporal
# order: 2601977 size: 36233450 {} [13705.362 ms; buffer=16] transposeWithDegree
# order: 2601977 size: 36233450 {} [91622.992 ms; buffer=32] readSnapTemporal
# order: 2601977 size: 36233450 {} [14023.922 ms; buffer=32] transposeWithDegree
# order: 2601977 size: 36233450 {} [97664.609 ms; buffer=64] readSnapTemporal
# order: 2601977 size: 36233450 {} [17388.348 ms; buffer=64] transposeWithDegree
# order: 2601977 size: 36233450 {} [104383.391 ms; buffer=128] readSnapTemporal
# order: 2601977 size: 36233450 {} [18472.646 ms; buffer=128] transposeWithDegree
# order: 2601977 size: 36233450 {} [99858.531 ms; buffer=256] readSnapTemporal
# order: 2601977 size: 36233450 {} [21877.215 ms; buffer=256] transposeWithDegree
# order: 2601977 size: 36233450 {} [105886.547 ms; buffer=512] readSnapTemporal
# order: 2601977 size: 36233450 {} [34482.242 ms; buffer=512] transposeWithDegree
# order: 2601977 size: 36233450 {} [124985.078 ms; buffer=1024] readSnapTemporal
# order: 2601977 size: 36233450 {} [45205.969 ms; buffer=1024] transposeWithDegree
# terminate called after throwing an instance of 'std::bad_alloc'
#   what():  std::bad_alloc
```

[![](https://i.imgur.com/1fWMaq8.gif)][sheets]
[![](https://i.imgur.com/vK1lXpi.gif)][sheets]

<br>
<br>


## References

- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/TDOVhqW.jpg)](https://www.youtube.com/watch?v=BHi4H2TfRjU)

[Prof. Dip Sankar Banerjee]: https://sites.google.com/site/dipsankarban/
[Prof. Kishore Kothapalli]: https://cstar.iiit.ac.in/~kkishore/
[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[charts]: https://photos.app.goo.gl/yaNq3gaEaufMT2ik9
[sheets]: https://docs.google.com/spreadsheets/d/1qV-G6d3inKgpEJedt-RcvmHSePkSqG1c477d2y5sLdk/edit?usp=sharing
