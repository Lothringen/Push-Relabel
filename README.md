# Push-Relabel
Two versions of the maximum flow algorithm in O(V^3) time

## Table of contents
* [General info](#general-info)
* [Setup](#setup)

## General info
Implementation of the push-relabel maximum-flow algorithm (Goldberg's version).

There are two implementations in O(V3):
* relabel-to-back (fifo queue)
* push-to-front (linked list)

Input: first line with total nodes n of the net, and total edges m. Followed by m lines with the directed edges and their cost. 
```
n m
v1 w1 c1
...
vm wm cm
```
Output: The maximum flux of the input net.
```
max flux
```

## Setup
To run this project, choose one of two possible algorithms = {back, front} and sample.in:

```
$ make
$ ./push_relabel -algorithm < sample.in
```


