                              ____________

                               P4 WRITEUP
                              ____________



PROBLEM 1: sumdiag_OPTM()
=========================

  Do your timing study on atlas.cselabs.umn.edu


(A) Paste Source Code
~~~~~~~~~~~~~~~~~~~~~

  Paste a copy of your source code for the function `sumdiag_OPTM()'


  int sumdiag_VER1(matrix_t mat, vector_t vec) {
  // OPTIMIZED CODE HERE
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }

  for(int i=0; i<vec.len; i++){                   // initialize vector of diagonal sums
    VSET(vec,i,0);                                // to all 0s
  }

  for (int i=0;i<mat.rows;i++){       //Loop across rows
    for (int j=0;j<mat.cols;j++){ //Lopp across columns
    VSET(vec,j-i+mat.cols-1,VGET(vec, j-i+mat.cols-1)+MGET(mat,i,j)); //Sets vector by calculating its diagonal, getting that
                                                                    //current value there, and then adding it to the element's value.
    }
  }
  return 0;
}


(B) Timing on atlas
~~~~~~~~~~~~~~~~~~~

  Paste a copy of the results of running `sudmiag_benchmark' on
  atlas.cselabs.umn.edu in the space below which shows how your
  performance optimizations improved on the baseline codes.

  ==== Matrix Diagonal Sum Benchmark Version 1 ====
  SIZE       BASE       OPTM  SPDUP POINTS
   512 4.8560e-03 2.0700e-03   2.35      2
  1024 2.4084e-02 8.3480e-03   2.89      2
  1101 2.8141e-02 9.7530e-03   2.89      2
  2048 2.5712e-01 3.4663e-02   7.42      7
  4099 1.0478e+00 1.4021e-01   7.47      7
  6001 2.3852e+00 3.0028e-01   7.94      7
  8191 9.4266e+00 5.7375e-01  16.43     16
RAW POINTS: 43
TOTAL POINTS: 35 / 35



(C) Optimizations
~~~~~~~~~~~~~~~~~

  Describe in some detail the optimizations you used to speed the code
  up.  THE CODE SHOULD CONTAIN SOME COMMENTS already to describe these
  but in the section below, describe in English the techniques you used
  to make the code run faster.  Format your descriptions into discrete
  chunks such as.
        Optimization 1: Blah bla blah... This should make run
        faster because yakkety yakeety yak.

        Optimization 2: Blah bla blah... This should make run
        faster because yakkety yakeety yak.

        ...  Optimization N: Blah bla blah... This should make run
        faster because yakkety yakeety yak.
  Full credit solutions will have a least two optimizations and describe
  WHY these improved performance in at least a couple sentences


  Optimization 1: Removed the two nested loops and condensed to a single nested loop (rearranged loops). This significantly
  increased time by lowering the amount of memory access that is happening. And allows the use of sequential
  memory accessing by iterating over rows then columns of the matrix significantly decreasing time because of its
  consecutive access to memory and its elements.

  Optimization 2: Removed local variable assignment/usage. Not a significant source of optimization but it decreased the workload
  of the program by removing the need to assign those variables and access their memory locations.

  Optimization 3: Used calculations to find the location of where the diagonal would need to be placed in the vector. This
  significantly decreased timproviding direct memory access to the program to those needed locations instead of having to take an iterative approach.


PROBLEM 2: Timing Search Algorithms
===================================

  Do your timing study on atlas.cselabs.umn.edu. In most cases, report
  times larger than 1e-03 seconds as times shorter than this are
  unreliable. Run searches for more repetitions to lengthen run times.


(A) Min Size for Algorithmic Differences
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  Determine the size of input array does one start to see a measurable
  difference in the performance of the linear and logarithmic
  algorithms.  Produce a timing table which includes all algorithms
  which clearly demonstrates an uptick in the times associated with some
  while others remain much lower.  Identify what size this appears to be
  a occur.


  Differences begin to happen when the array hits size 4096. while the linked list
  performance begins to become slower then the array in linear search, the binary search and binary
  tree remain relatively at equal performance.

  ./search_benchmark 9 14 5
Length:    512
Length:   1024
Length:   2048
Length:   4096
Length:   8192
Length:  16384

 array
4.9830e-03
1.9842e-02
7.9015e-02
3.1640e-01
1.2618e+00
5.0445e+00
  list
5.0050e-03
5.5058e-02
2.6096e-01
1.2922e+00
7.1653e+00
3.3024e+01
binary
3.6500e-04
7.7400e-04
1.4650e-03
2.9910e-03
6.3200e-03
1.3702e-02
  tree
2.5800e-04
5.4500e-04
1.1830e-03
2.4980e-03
5.4250e-03
1.3026e-02



(B) Linear Search in List vs Array
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  Determine whether the linear array and linked list search remain
  approximately at the same performance level as size increases to large
  data or whether one begins to become favorable over other. Determine
  the approximate size at which this divergence becomes obvious. Discuss
  reasons WHY this difference arises.

  The Linked List's performance is worse when size becomes increasing larger of the array. The size in
  which this divergence happens is when the length of the array reaches 4096. This difference is because
  an array has better cache locality in which it's contents can be accessed sequentially while linked
  lists require more memory to store pointers and traversing over large quanities of it is costly.


  Length:    512
Length:   1024
Length:   2048
Length:   4096
Length:   8192
Length:  16384

 array
9.9600e-04
3.9790e-03
1.5845e-02
6.3165e-02
2.5248e-01
1.0100e+00
  list
9.9900e-04
1.1034e-02
5.2285e-02
2.5867e-01
1.4343e+00
6.6166e+00


(C) Binary Search in Tree vs Array
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  Compare the binary array search and binary tree search on small to
  very large arrays. Determine if there is a size at which the
  performance of these two begins to diverge. If so, describe why this
  might be happening based on your understanding of the data structures
  and the memory system. If not, describe why you believe there is
  little performance difference between the two.

  The performance of both the binary array search and binary tree search from large
  to small are relatively the same. This is because they both use the same algorithm
  of dividing and conquering which in both cases run at near O(logn) no matter the size. The
  cache effect is that locality is increased as more and more elements are eliminated from the search.

./search_benchmark 10 20 5 bt
Length:   1024
Length:   2048
Length:   4096
Length:   8192
Length:  16384
Length:  32768
Length:  65536
Length: 131072
Length: 262144
Length: 524288
Length: 1048576

binary
6.8200e-04
1.4000e-03
3.0000e-03
6.4130e-03
1.3704e-02
2.9801e-02
6.6721e-02
1.5082e-01
3.4146e-01
7.6597e-01
1.7291e+00
  tree
5.0900e-04
1.0780e-03
2.2760e-03
4.9280e-03
1.0531e-02
2.2625e-02
6.5854e-02
1.7456e-01
4.1987e-01
1.0126e+00
2.1071e+00





(D) Caching Effects on Algorithms
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  It is commonly believed that memory systems that feature a Cache will
  lead to arrays performing faster than linked structures such as Linked
  Lists and Binary Search Trees. Describe whether your timings confirm
  or refute this belief.  Address both types of algorithms in your
  answer:
  - What effects does Cache have on Linear Search in arrays and lists
    and why?
  - What effects does Cache have on Binary Search in arrays and trees
    and why?

    My findings were that the linear search of an array was faster then that of the
    linked list and the binary search of the array had no significant performance
    difference in comparison to the binary tree search. This is because the linear array
    has better cache locality then the linked list so it needs less memory and can be accessed
    in succession through larger arrays. The binary search and binary trees are both improve cache locality
    over its duration because it eliminates half of its possible references each step. Therefore based on my timing,
    the linear array search did perform faster for large amounts of elements in comparison to the linked list, but its performance
    was less then that of binary searches in arrays and trees because of those two's improvement in cache locality in each run.

(E) OPTIONAL MAKEUP CREDIT
~~~~~~~~~~~~~~~~~~~~~~~~~~

  If you decided to make use of a table of function pointers/structs
  which is worth makeup credit, describe your basic design for this
  below.
