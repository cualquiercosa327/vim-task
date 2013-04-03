#!/bin/bash

g++ shift-random-repeats.cpp -o shift-random-repeats
g++ random.cpp -o random
g++ alternating-random.cpp -o alternating-random


## EASY CASE (40 points)
# TODO (maybe not so much grouping?)

# 10 points: 200
mkdir 4
./shift-random-repeats 4985 5 > 4/0.in
./random 4952 10 | sed 's/^e+//' > 4/1.in

# 10 points: 200
mkdir 5
./shift-random-repeats 4980 6 > 5/0.in
./random 4809 7 > 5/1.in
./alternating-random 5000 8 > 5/3.in
./shift-random-repeats 5000 9 > 5/2.in

# 10 points: 200
mkdir 6
./shift-random-repeats 9999 11 > 6/0.in
./random 9999 12 > 6/1.in
./alternating-random 10000 13 > 6/2.in

# 10 points: 400
mkdir 6
./shift-random-repeats 9999 11 > 6/0.in
./random 9999 12 > 6/1.in
./alternating-random 10000 13 > 6/2.in


## MEDIUM CASE (30 points)

# 10 points: 5000
mkdir 4
./shift-random-repeats 4985 5 > 4/0.in
./random 4952 10 | sed 's/^e+//' > 4/1.in

# 15 points: 5000
mkdir 5
./shift-random-repeats 4980 6 > 5/0.in
./random 4809 7 > 5/1.in
./alternating-random 5000 8 > 5/3.in
./shift-random-repeats 5000 9 > 5/2.in

# 5 points: 10000
mkdir 6
./shift-random-repeats 9999 11 > 6/0.in
./random 9999 12 > 6/1.in
./alternating-random 10000 13 > 6/2.in


## HARD CASE (30 points)
# TODO more subcases

# 10 points: 65000
mkdir 7
./shift-random-repeats 65000 14 > 7/0.in
./random 65000 15 > 7/1.in
./alternating-random 65000 16 > 7/2.in

# 10 points: 70000
mkdir 8
./shift-random-repeats 70000 17 > 8/0.in
./random 70000 18 > 8/1.in
./shift-random-repeats 70000 19 > 8/2.in
./alternating-random 70000 20 > 8/3.in

# 10 points: 80000
mkdir 9
./shift-random-repeats 80000 21 > 9/0.in
./random 80000 22 > 9/1.in
./alternating-random 80000 23 > 9/2.in
