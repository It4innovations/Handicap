# About
Magic-type labelings are a well established topic of graph theory.
There are hundreds of scientific papers published. For a comprehensive
overview we recommend Gallians Dynamic Survey of Graph Labeling
published in the The Electronic Journal of Combinatorics and updated
annually.

Given a certain labeling there are typically three types of results:
- i) constructions of the labeling for a specific class of graphs,
- ii) nonexistence results based on structure or parity
- iii) construction of graphs with a specified parameters e.g. order,
regularity.

Our contribution is mostly to the second and third branch. Typically, an
inductive construction is given that exploits all feasible values of
given parameters and for the remaining values non-existence is proven.


# Acknowledgement
This work was supported by The Ministry of Education, Youth and Sports
from the National Programme of Sustainability (NPU II) project
„IT4Innovations excellence in science - LQ1602“ and by the
IT4Innovations infrastructure which is supported from the Large
Infrastructures for Research, Experimental Development and Innovations
project „IT4Innovations National Supercomputing Center – LM2015070“.


# Quick install

Installation is very simple on operating systems Linux\MacOsX

## Before we start

Please check the necessary program requirements on your local machine.
- compiler ***g++*** at  version  4.2.1 or greater with support lang std=c++11
- command for a g++ compiler test version ```g++ -v```
- a ***Make*** manager for a building program on your local machine
- the command for a make manager exists ```make --help``` if not please install them.
- ***git*** client for download a project from gitlab server
- the command for a exists git client on the machine ```git --version``` if not please install them on this sites [https://git-scm.com/downloads](https://git-scm.com/downloads)

## Download and install project

For this purpose, we use git client.
At the first step, we will open terminal and execute command ```git clone https://code.it4i.cz/ADAS/ExtendingHandicapGraphLabeling```.
After that, we open folder `ExtendingHandicapGraphLabeling` via command `cd ExtendingHandicapGraphLabeling` and 
enter the final command for compilation `make`.

## Running a program

After entering the command `make`, we will find execute file name `ExtendingHandicapGraphLabeling`. 
For correct test, please enter a command ```./ExtendingHandicapGraphLabeling```. Program in default settings prints all ten 4-regular graphs with extended handicap labeling.

For searching another graphs, please edit parameters in the file `src\main.cpp`. There are defined global constants:
- ***THREAD_COUNTS*** - there is a number of threads for making parallelism, it is recommended set value like as number of CPUs -1
- ***REGULAR_GRAPHS*** - there is a number of regularity graphs
- ***VERTICES_COUNT*** - there is a number of vertices
- ***START_LABEL*** - there is a first labeled label at the searching process

# Benchmark 
We tested this program on Anselm computres cluster of IT4I.cz. Program ran at one node which included 16 CPUs. The scaling factor, you can see on image. 
We search all a 4-regular graphs on 20 vertices with extended handicap labeling. 

![Benchmark]( documentation/benchmark.png?raw=true "Benchmark")

# Parallelism  
The main idea is a brute-force search for all feasible permutations  of
labels that yield a regular graph with the extended handicap labeling.
The search space is reduced by pruning branches that clearly do not
allow this particular labeling.
The key building block is generating for each vertex only such list of
neighbors that have the required weight. Then each such list is pushed
to a thread-safe queue. After that, the program runs a given number of N
threads, where each thread explores one branch of the search space. If s
thread is finished, it will pick up the next job from the queue (pool).
This model of parallelism is called ThreadPool.
Moreover, the execution can be stopped once at least one job gave a
positive answer: when a graph with the extended handicap labeling and
given order and regularity was found.

# Example
We prepared some example of this program. If you set the main constantats for:
REGULARITY: 4, VERTICES_COUNT = 12, THREAD_COUNT = 1, STARTING_LABEL = 1 and after that save the file main.cpp. Compaile it and run it. The result will be same like file locates in test/result4-12.txt. The result has got 10 results of labeling graphs.

# License
This project is made available under the BSD 2-Clause License.
