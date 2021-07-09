#include <stdio.h>
#include <string.h>
#include "treemap.h"



int main(int argc, char *argv[]){
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }

//Commands to look for in echo/display
  printf("TreeMap Editor\n");
  printf("Commands:\n");
  printf("  quit:          exit the program\n");
  printf("  print:          shows contents of the tree in reverse sorted order\n");
  printf("  add <key> <val>: inserts the given key/val into the tree, duplicate keys are ignored\n");
  printf("  get <key>:       prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
  printf("  clear:           eliminates all key/vals from the tree\n");
  printf("  preorder:        prints contents of the tree in pre-order which is how it will be saved\n");
  printf("  save <file>:     writes the contents of the tree in pre-order to the given file\n");
  printf("  load <file>:     clears the current tree and loads the one in the given file\n");
  char key[128]; // array of keys
  char val[128]; // array of values
  char cmd[128]; //input array
  int success;
  treemap_t tree; // tree variable
  treemap_init(&tree); // initializes tree to an empty tree

  while(1){
    printf("TM> ");
    success = fscanf(stdin,"%s",cmd); // read a command
    if(success==EOF){                 // check for end of input
      printf("\n");                   // found end of input
      break;                          // break from loop
    }
    if( strcmp("quit", cmd)==0 ){ //quit command
    fscanf(stdin, "%s", cmd);
      if(echo){
            printf("quit\n");
      }
      break; //break from loop to clear statement

                        // break from loop
    }


    else if( strcmp("print", cmd)==0 ){ //print command
      if(echo){
        printf("print\n");
      }
      treemap_print_revorder(&tree); //call treemap function to print reverse order

    }

    else if( strcmp("get", cmd)==0 ){ // get command
      fscanf(stdin,"%s",key);  //scans input to key array
      if(echo){
        printf("get %s\n", key); //prints if echo
      }

      char *i = treemap_get(&tree, key); // calls treemap get function and assigned return value
                                        // i.
      if(i == NULL){
        printf("NOT FOUND\n");
      }
      else {
        printf("FOUND: %s\n", i);
      }
    }

    else if( strcmp("clear", cmd)==0 ){   // clear command
      if(echo){
        printf("clear\n");
      }
      treemap_clear(&tree); //treemap call function that clears tree
    } else if( strcmp("save", cmd)==0 ){ //save command
        fscanf(stdin, "%s", cmd);
      if(echo){
        printf("save %s\n", cmd);
      }
      treemap_save(&tree, cmd); //treemap call function to save function

      }

    else if( strcmp("preorder", cmd)==0 ){   // print command
      if(echo){
        printf("preorder\n");
      }
      treemap_print_preorder(&tree); //treemap call function to print in preorder

      }else if( strcmp("add", cmd)==0 ){ //add command
      fscanf(stdin,"%s %s",key, val); //scans input to key and value arrays
      if(echo){
        printf("add %s %s\n",key, val);
      }
      int t;

      t = treemap_add(&tree, key, val); //call tree map function to add
      if(t == 0){                       //check for success
        printf("modified existing key\n");

    }
      } else if( strcmp("load", cmd)==0 ){ //load command
          fscanf(stdin, "%s", cmd);
      if(echo){
        printf("load %s\n", cmd);
      }
      int temp;
      temp = treemap_load(&tree, cmd); // call treemap function to load
      if (temp ==0){                   // check for success
        printf("load failed\n");
      }

      }

    else{                                 // unknown command
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command %s\n",cmd);
    }
  }
  treemap_clear(&tree); //clears tree
  return 0;
}

