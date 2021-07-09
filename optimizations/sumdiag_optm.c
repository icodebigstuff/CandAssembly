// optimized versions of matrix diagonal summing
#include "matvec.h"

// You can write several different versions of your optimized function
// in this file and call one of them in the last function.

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

int sumdiag_VER2(matrix_t mat, vector_t vec) {
  // OPTIMIZED CODE HERE
  if(vec.len != (mat.rows + mat.cols -1)){
    printf("sumdiag_base: bad sizes\n");
    return 1;
  }
  for(int i=0; i<vec.len; i++){                   // initialize vector of diagonal sums
    VSET(vec,i,0);                                // to all 0s
  }

  int maxdiag = (mat.rows+mat.cols)-1;            // calculate last diagonal
  for(int d=mat.rows; d < maxdiag ; d++){         // iterate starting at first upper diag
    int r = 0;
    int el_rc =0;
    int vec_d =0;                                // row always starts at 0 in upper diags
    for(int c=d-mat.cols+1; c<mat.cols; r++,c++){ // work down rows, right cols for same diag
      el_rc += MGET(mat, r, c);                // matrix element
      vec_d += VGET(vec, d);                   // diagonal sum from vector
                    // add on to sum
    }
    VSET(vec, d, el_rc+vec_d);
  }

  for(int d=0; d < mat.rows; d++){                // iterate over lower diagonals
    int c = 0;
    int el_rc =0;
    int vec_d =0;                               // col always starts at 0 in lower diags
    for(int r=mat.rows-d-1; r<mat.rows; r++,c++){ // work down rows, right cols for same diag
      el_rc += MGET(mat, r, c);                // get matrix element on diagonal
      vec_d += VGET(vec, d);                   // retrieve current sum for diag
                       // add on back to the diagonal sum
    }
    VSET(vec, d, el_rc+vec_d);
  }


  return 0;

}



int sumdiag_OPTM(matrix_t mat, vector_t vec) {
  // call your preferred version of the function
  return sumdiag_VER1(mat, vec);
}
