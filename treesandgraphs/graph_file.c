#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"

//Graphing main function that uses both functions in deltas_main.c and
//print function in print_graph.c

int main(int argc, char *argv[]){
  if(argc < 3){
    //Commands
    printf("usage: %s <format> <filename>\n",argv[0]);
    printf(" <format> is one of\n");
    printf(" text : text ints are in the given filename\n");
    printf(" int  : binary ints are in the given filename\n");
    printf(" 4bit : 4bit binary ints are in the given filename\n");
    return 1;
  }
  char *format = argv[1]; //format of graph
  char *fname = argv[2]; //filename to read
  char *height = argv[3];//maximum height of graph

  int max_height = atoi(height); //converts height to an int

  int data_len = -13; // length of the data array
  int *data_vals = NULL; //pointer to a data array
  if( strcmp("text", format)==0 ){ //text command
    printf("Reading text format\n");
    data_vals = read_text_deltas(fname, &data_len); //call to read text deltas function
  }
  else if( strcmp("int", format)==0 ){ //int command
    printf("Reading int format\n");
    data_vals = read_int_deltas(fname, &data_len); //call to read int deltas function
  }

  else{ //unknown command
    printf("Unknown format '%s'\n",format);
    return 1;
  }

  if(data_vals != NULL){
    print_graph(data_vals, data_len,max_height); //call to print graph function
    printf("\n");
    free(data_vals);
  }
  else{
    printf("Returned NULL pointer\n");
    printf("Read %d ints\n",data_len);
  }

  return 0;
}
