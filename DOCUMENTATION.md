insalg - Documentation
======================

Lukáš Folwarczný, <lfolwarczny@gmail.com>

Up-to-date version of this document as well as the whole project are
available on my website: <http://atrey.karlin.mff.cuni.cz/~folwar/insalg/>

About insalg
------------

Instant Algorithms (insalg) is a library of algorithms implemented
in C++.

This library should provide more or less standard algorithms to be
used in algorithmic tasks, especially during competitions.

Algorithms in this library may be included in other projects and used
as a black box. However, this is not the primary intention.
I coded these algorithms for this specific situation:
I know the principle of some algorithm and I want to reuse it and
modify it for some task. These implementations should spare me the
time for inventing all the implementation details.

That implies the style of all the code here:
The code should be short, easily understandable, rather than complex,
universal and highly optimized. (But all the implementations here
should be effective.)

The code is C++ because of some advantages that can spare much time,
but the use of C++ features is very conservative.
Most of the code resembles more C rather than C++.

For the situation, when one cannot have his computer with him, there
is also a PDF version of the implementations.

Usage
-----

### C++ code

All source codes are located in the ./code directory. The filenames are
in the format [category]-[algorithm].cpp, e. g.
string-suffix_array.cpp.

Each file contains a brief description of the algorithm, in some cases
also the reference to an article describing the algorithm.

There is a demo function in each file, usually named [algorithm]_demo.
I used the demo functions for testing and it illustrates the proper
use of the specific algorithm.

If the macro RUNDEMO is defined, then the main function running the
demo is also there, so it can be run instantly.

To simply run demo, you can use makefile in the code directory, which
will add the RUNDEMO macro and compile the code. Use file name without
extension. If you, for example, want to run demo of the suffix array,
run these commands:

	cd code
	make string-suffix_array
	./string-suffix_array


### PDF version

You can generate a PDF version of the code with a make command in the
*pdf* directory (make, awk and pdflatex are required).

Generated PDF file is available online:
<http://atrey.karlin.mff.cuni.cz/~folwar/insalg/insalg.pdf>

The code in the PDF version is not a complete copy of the .cpp files.
In each .cpp file, every part to be included in PDF is bounded by two
tags /\*pdf\*/.

----------------------------------------
Quick overview of implemented algorithms
----------------------------------------

This overview tells you what to expect from each file, more details
are in the .cpp files themselves.

In the sake of lucidity, the algorithms are split into categories:

*	Geometry
*	Number
*	Sort
*	Permutation
*	String
*	Heap
*	Interval
*	Flow

##### template.cpp

A basic code that is included in all other codes.
It contains includes and few macros.

##### Geometry

###### geometry-geometric_median.cpp

A single function *geometric_median* runs given number of iterations of Weiszfeld's algorithm to
approximate the geometric median.

##### Number
###### number-eratosthenes.cpp

Eratosthenes siege running in *O(n log log n)* time.

###### number-euclid.cpp

Basic and extended Euclid algorithm.

#### Sort
###### sort-quicksort.cpp

Ordinary quick sort implementation.

###### sort-kth_smallest.cpp

Computes the *k*-th element of the array in linear time using Median
of Medians algorithm.

#### Permutation
###### permutation-bijection.cpp

Constructs the bijection between permutations of the length *N* and
numbers *{0,1,...,N!-1}*.

The functions *integer_to_permutation* and *permutation_to_integer*
provide the conversions.

Time complexity for a single conversion is *O(N^2)*.

#### Heap
###### heap-binary.cpp

Binary minimum heap. To use the heap, the function *make* must be called.
*make* runs in *O(N)* time, operations *delete_min* and *insert* in *O(log N)*.

#### Interval
###### interval-max_tree.cpp

Maximum interval tree. Interval tree is built in *O(N)* time
with the function *make* and handles two queries in *O(log N)* time:
To update an element of a given element and to compute the maximum
of a given interval.

###### interval-max_array.cpp

Immutable array requiring *O(N log N)* space.
Interval maximum query is performed in *O(1)* time.

###### interval-fenwick.cpp

The Fenwick tree is a very elegant equivalent of the summing
interval tree.

#### String

###### string-kmp.cpp

Knuth-Morris-Pratt algorithm. Failer function is computed with the
function *build*. The search of a given word is performed by the
function *search*.

###### string-minlexrot.cpp

The Booth's algorithm for finding the lexicographically minimal
rotation of a given string.

Algorithm is an elegant modification of KMP.

###### string-aho_corasick.cpp

Aho-Corasick algorithm, searches ocurrences of words from a given dictionary in a given
text.

###### string-suffix_array.cpp

Suffix array construction in *O(N)* time with the 2/3 recursion.

#### Graph
###### graph-dfs.cpp

A simple implementation of the Depth-First Search with *in* and *out*
time stamps. The input graph is represented by a list of neighbours
for each vertex.

###### graph-tarjan_scc.cpp

The Tarjan's algorithm for the identification of strongly
connected components.

#### Flow
###### flow-ford_fulkerson.cpp

The standard Ford-Fulkerson algorithm with BFS.

###### flow-ford_goldberg.cpp

The Goldberg (also known as push-relabel) algorithm, finds max flow in O(N^3).

This implementation is only an alpha version, I will update soon.
