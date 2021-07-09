#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"
#include <sys/stat.h>
// read_text_deltas function: Reads integers in text delta format from the file named by fname
// and returns an array of them. The first integer in the file gives
// the starting point and subsequent integers are changes from the
// previous total.
//
// Opens the file with fopen() and scans through its contents using
// fscanf() counting how many text integers exist in it.  Then
// allocates an array of appropriate size using malloc(). Uses
// rewind() to go back to the beginning of the file then reads
// integers into the allocated array. Closes the file after reading
// all ints.  Returns a pointer to the allocated array.
//
// The argument len is a pointer to an integer which is set to the
// length of the array that is allocated by the function.
//
// If the file cannot be opened with fopen() or if there are no
// integers in the file, sets len to -1 and returns NULL.

int *read_text_deltas(char *fname, int *len){
    FILE *file;
    file = fopen(fname, "r"); //opens file
    if (file == NULL){
        *len = -1;
        return NULL;
    }
    int i;
    int num;
    int count = 0;

    while (fscanf(file,"%d", &num) != EOF)  { //counts length of file
        ++count;
    }
    if(count != 0){
        *len = count;
        int *ptr = (int*) malloc(*len * sizeof(int)); //allocates new array

    rewind(file);

    for (i =0; i< *len; ++i){ //reads file into array
        fscanf(file, "%d", &ptr[i]);
    }

    int j;
    for (j =1; j< *len; ++j){ //delta computation
        int prev = ptr[j-1];
        ptr[j] = ptr[j] + prev;
    }
    fclose(file);
    return ptr;
    } else{
    fclose(file);
    *len = -1;
    return NULL;
    }
}

// read_int_deltas function : Reads integers in binary delta format from the file named by fname
// and returns an array of them.  The first integer in the file gives
// the starting point and subsequent integers are changes from the
// previous total. Uses the stat() system
// call to determine the file size in bytes which then allows an array
// of appropriate size to be allocated.
// Opens the file with fopen() and uses repeated calls to fread() to
// read binary integers into the allocated array. Does delta
// computations as integers are read. Closes the file after reading
// all ints.
//
// The argument len is a pointer to an integer which is set to
// the length of the array that is allocated by the function.
//
// If the file cannot be opened with fopen() or file is smaller than
// the size of 1 int, sets len to -1 and returns NULL.

int *read_int_deltas(char *fname, int *len){
    FILE *file;
    file = fopen(fname, "r"); //opens file
    if (file == NULL){
        *len = -1; //sets lebn to -1
        return NULL;
    }

    struct stat stats; //makes stat struct
    int values = stat(fname, &stats);
    if(values == -1 || stats.st_size <sizeof(int)){ //checks size
        fclose(file);
        *len = -1;
        return NULL;
    }
    int bytes = stats.st_size;
    *len = bytes/4;
    int *ptr = malloc(bytes); //allocates new ptr array
    int i;

    for(i =0; i<*len; ++i){
        if (i ==0){
            fread(&ptr[i], sizeof(int),1, file ); // assigns file values to ptr indices

        } else{

            fread(&ptr[i], sizeof(int), 1, file);
            int prev = ptr[i-1];
            ptr[i] = ptr[i] + prev; //delta computation
        }
    }

    fclose(file);




    return ptr; //returns pointer to the array

}



