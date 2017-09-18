# mutual-exclusion

This project contains implementation of mutual exclusion algorithms - Lamport's bakery algorithm and Peterson's tournament algorithm. Multiple threads request for lock for execution of critical section. Algorithm to use for mutual exclusion is given input at runtime.
Each thread requests lock once, executes critical section and exits. It records the time required to enter and exit critical section, and stores it in a CSV file. This implementation is in C++11.

### System requirement
1. GCC (or any other compiler using C++11)
2. <code>make</code> utility

### How to build
Navigate to the root directory of the project and make the project.
<pre>
<code>
$ cd mutex
$ make clear
$ make
</code>
</pre>

### How to execute
Execute the binary file with options.
You need to specify the algorithm to use, number of threads to start. You can also specify the path of the output file.
<pre>
<code>
$ ./mutex <tournament|bakery> <n> [<output-file.csv>]
</code>
</pre>

To execute for bakery algorithm with 500 threads:
<pre>
<code>
$ ./mutex bakery 500 ../bakery.csv
</code>
</pre>

