## This file contains the codes for getting minors from a nxn matrix.

- Serial.cpp : Contains the program for serially getting the minors without parallelizing the computations among available processors.
- Parallel.cpp : Contains the program for parallelizing thr minor computations among available processors evenly, for example, total number of minirs that can be calculated = 25, available processors = 4, then P0, P1, P2 will have to calculate 6 minors each, and the last processor P3 will have to calculate 7 minors.