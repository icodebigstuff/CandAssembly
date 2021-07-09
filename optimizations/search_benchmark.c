#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "search.h"
#include <time.h>


//Main function that times the use of various search funcsions provided in search_func.c and included in the search.h header.

int main(int argc, char *argv[]){

    int do_linear_array =0; // run linear array search if 1
    int do_linear_list =0; //run linear linked list search if 1
    int do_binary_array =0; //run binary search on array if 1
    int do_binary_tree =0; //run binary search on tree if 1
    if(argv[1] == NULL || argv[2] == NULL || argv[3] == NULL){   //Loop that prints an error if the sizes and repeats of the array are omitted in command line
    printf("ERROR: inputs must be <min_pow> <max_pow> <repeats>\n");
    return 1;
    }

    int min_pow = atoi(argv[1]); //store the initial exponential length of array in min_pow
    int max_pow = atoi(argv[2]); //stores the maximum exopnential length of the array in max_pow
    int repeats = atoi(argv[3]); //number of repeats


    if (argv[4] == NULL){ //if a,l,b, or t is not specified, sets all to run
        do_binary_tree =1;
        do_linear_array =1;
        do_binary_array =1;
        do_linear_list =1;
    } else{
    char *algs_string = argv[4];
    for(int i=0; i < strlen(algs_string); i++){ //loop that iterates and sets which searches to run

    if(algs_string[i] == 'a'){
      do_linear_array = 1;
    }
    if(algs_string[i] == 'l'){
      do_linear_list = 1;
    }
     if(algs_string[i] == 'b'){
      do_binary_array = 1;
    }
    if(algs_string[i] == 't'){
      do_binary_tree = 1;
    }
  }
  }




//Loop that prints length
for(int l=min_pow;l<=max_pow;l++){
    int length = 1 << l;
    printf("Length: %6d     ",length );
    printf("\n");
}
printf("\n");

if (do_linear_array == 1){
    printf("%6s ","array"); //Array title print
 printf("\n");
}

//Outer loop that goes from the minimum power to the max
for (int j =min_pow;j<=max_pow;j++){
int success = 0; //success count
 if (do_linear_array == 1){
    int length = 1 << j; //right shifts lengths to adjust size of array
    int *array = make_evens_array(length); //array is a pointer to the array generated from make_evens_array

    clock_t begin, end;
    begin = clock();

    for(int i=0; i<repeats; i++){ //outter loop repeats
    for (int m =0;m<length*2;m++){  //inner loop for search times
    success+= linear_array_search(array,length,m); //records success of finding query
    }
    }
    if (success != length*repeats){ //Error checking
    printf("ERROR\n");
    return 1;

    }
    end = clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC; //time of function run
    printf("%10.4e\n", time);

    free(array);
  }



}

//Print list label
if (do_linear_list == 1){
    printf("%6s ","list");
 printf("\n");
}

//Outer loop that goes from the minimum power to the max
for (int j =min_pow;j<=max_pow;j++){
  if (do_linear_list == 1){
  int success = 0; //count successes if query found
  int length = 1<<j; //right shifts length to adjust size of list
    list_t *lnlist = make_evens_list(length); //lnlist is pointer to linked list of even values
    clock_t begin, end;
    begin = clock();
    for(int i=0; i<repeats; i++){ //outter loop for repeats

      for (int m =0;m<length*2;m++){ //inner loop for searches
        success += linkedlist_search(lnlist,length,m); //success records 1 and 0s for hits or misses
      }

    }
    if (success != length*repeats){ //Error checking
        printf("ERROR\n");
        return 1;
    }
    end = clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC; //calculate total time of search
    printf("%10.4e\n", time);
    list_free(lnlist);
  }
  }

//print binary label for binary search array
  if (do_binary_array == 1){
    printf("%6s ","binary");
 printf("\n");
}

//Outer loop that goes from the minimum power to the max
for (int j =min_pow;j<=max_pow;j++){
      if (do_binary_array == 1){

    int success = 0; //success count
    int length = 1<<j; //right shifts length to adjust size of array
    int *arr = make_evens_array(length); //arr is a pointer to an list of even values
    clock_t begin, end;
    begin = clock();
    for(int i=0; i<repeats; i++){ //outer loop for repeats
    for (int m =0;m<length*2;m++){ //inner loop for searches
    success+= binary_array_search(arr, length,m); //records success or fails by adding 1s or 0s
    }
    }
    if (success != length*repeats){ //Error checking
    printf("Error\n");
    return 1;

    }
    end = clock();
      double time = ((double) (end - begin)) / CLOCKS_PER_SEC; //total time calculated for search
    printf("%10.4e\n", time);

    free(arr);
  }
  }


//prints tree label
if (do_binary_tree == 1){
  printf("%6s ", "tree");
printf("\n");
}

//Outer loop that goes from the minimum power to the max
for(int j=min_pow;j<=max_pow;j++){
  if (do_binary_tree == 1){
  int success =0; //success count
  int length = 1<<j; //right shifts length to adjust tree size
    bst_t *tree = make_evens_tree(length); //tree is a pointer to a binary tree of even values
    clock_t begin, end;
    begin = clock();
    for(int i=0; i<repeats; i++){ //outer loop for repeats
      for (int m =0;m<length*2;m++){ //inner loop for searches
        success += binary_tree_search(tree,length,m); //counting success/fails (0s/1s) of binary tree search function
      }

    }
    if(success != repeats*length){ //Error checking
        printf("ERROR\n");
        return 1;
    }

    end = clock();
      double time3 = ((double) (end - begin)) / CLOCKS_PER_SEC; //calculate total time of search
    printf("%10.4e ", time3);
    printf("\n");
    bst_free(tree);

  }

}




  return 0;

}

