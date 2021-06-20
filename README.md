Performance of **static** vs **dynamic** [levelwise] PageRank.

This experiment was for comparing performance between:
1. Find **static** [monolithic] pagerank of updated graph.
2. Find **dynamic** [monolithic] pagerank of updated graph.
3. Find **static** [levelwise] pagerank of updated graph.
4. Find **dynamic** [levelwise] pagerank of updated graph.

Each approach was attempted on a number of temporal graphs, running each with
multiple batch sizes (`1`, `5`, `10`, `50`, ...). Each batch size was run with 5
different updates to graph, and each specific update was run 5 times for each
approach to get a good time measure. Indeed, **dynamic levelwise** pagerank is
**faster** than the *static* approach for many batch sizes.

All outputs are saved in [out](out/) and a small part of the output is listed
here. Some [charts] are also included below, generated from [sheets]. The input
data used for this experiment is available at the
[Stanford Large Network Dataset Collection].

<br>

```bash
$ g++ -O3 main.cxx
$ ./a.out ~/data/email-Eu-core-temporal.txt

# (SHORTENED)
# Using graph email-Eu-core-temporal.txt ...
# Temporal edges: 332335
# order: 986 size: 24929 {}
#
# # Batch size 1e+0
# [00000.498 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.032 ms; 002 iters.] [6.4766e-7 err.] pagerankDynamic
#
# # Batch size 5e+0
# [00000.510 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.065 ms; 003 iters.] [1.0864e-6 err.] pagerankDynamic
#
# # Batch size 1e+1
# [00000.501 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.098 ms; 005 iters.] [1.5461e-6 err.] pagerankDynamic
#
# # Batch size 5e+1
# [00000.503 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.218 ms; 011 iters.] [2.4047e-6 err.] pagerankDynamic
#
# # Batch size 1e+2
# [00000.502 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.251 ms; 014 iters.] [2.4436e-6 err.] pagerankDynamic
#
# # Batch size 5e+2
# [00000.499 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.308 ms; 016 iters.] [2.5226e-6 err.] pagerankDynamic
#
# # Batch size 1e+3
# [00000.501 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.336 ms; 018 iters.] [2.4926e-6 err.] pagerankDynamic
#
# # Batch size 5e+3
# [00000.509 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.391 ms; 020 iters.] [2.3684e-6 err.] pagerankDynamic
#
# # Batch size 1e+4
# [00000.518 ms; 027 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.415 ms; 022 iters.] [2.1345e-6 err.] pagerankDynamic
#
# # Batch size 5e+4
# [00000.530 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.481 ms; 022 iters.] [1.6988e-6 err.] pagerankDynamic
#
# # Batch size 1e+5
# [00000.577 ms; 024 iters.] [0.0000e+0 err.] pagerankStatic
# [00000.541 ms; 022 iters.] [1.5049e-6 err.] pagerankDynamic
```

[![](https://i.imgur.com/4tWWPOT.gif)][sheets]
[![](https://i.imgur.com/VAHYT9C.gif)][sheets]

<br>
<br>


## References

- [Stanford Large Network Dataset Collection]

<br>
<br>

[![](https://i.imgur.com/0TfMELc.jpg)](https://www.youtube.com/watch?v=npl0o3X7NTA)

[Stanford Large Network Dataset Collection]: http://snap.stanford.edu/data/index.html
[charts]: https://photos.app.goo.gl/dcQWY7z1HEdPAqre8
[sheets]: https://docs.google.com/spreadsheets/d/1b6fuE9dRbAbQanCl2rDXc-K2xpIUSg7Mw_dzVnFbkD8/edit?usp=sharing
