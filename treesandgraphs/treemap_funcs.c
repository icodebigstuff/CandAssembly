#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
// treemap_funcs.c: Provides a small library of functions that operate on
// binary search trees mapping strings keys to string values.


// treemap_init: function that initializes the given tree to have a null root and have size 0.

void treemap_init(treemap_t *tree){
    tree->root = NULL;
    tree->size = 0;
}

// treemap_add: Inserts given key/value into a binary search tree. Uses an
// ITERATIVE (loopy) approach to insertion which starts a pointer at
// the root of the tree and changes its location until the correct
// insertion point is located. If the key given already exists in the
// tree, no new node is created; the existing value is changed to the
// parameter 'val' and 0 is returned.  If no node with the given key
// is found, a new node is created and with the given key/val, added
// to the tree, and 1 is returned. Makes use of strcpy() to ease
// copying characters between memory locations.
int treemap_add(treemap_t *tree, char key[], char val[]){ //takes the tree, and key/val to be added
    if (tree->root == NULL){
        node_t *temp = malloc(sizeof(node_t)); //creates new node to add as root
        temp->left = NULL;
        temp->right = NULL;
        strcpy(temp->key, key);
        strcpy(temp->val, val);
        tree->root = temp;
        tree->size++;
        return 1;
    } node_t *t = tree->root; // variable that indicates the current node (in this case the root)
        while (1){
          if (strcmp(t->key, key)== 0){ //checks to see if the current node's key is equal to the added key
            strcpy(t->val, val);
            return 0;
            } else if(strcmp(t->key, key) > 0){ // checks to see if the current node's key is greater then the key
                if( t->left == NULL){
                    node_t *temp = malloc(sizeof(node_t)); //makes new node to add to tree
                    temp->left = NULL;
                    temp->right = NULL;
                    strcpy(temp->key, key);
                    strcpy(temp->val, val);
                    t->left = temp;
                    tree->size++;
                    return 1;
                } else{
                    t = t->left;
                }
            } else if(strcmp(t->key, key) < 0){ // checks to see if current node's key is less then the key
                if(t->right == NULL){
                    node_t *temp = malloc(sizeof(node_t));
                    temp->left = NULL;
                    temp->right = NULL;
                    strcpy(temp->key, key);
                    strcpy(temp->val, val);
                    t->right = temp;
                    tree->size++;
                    return 1;
                } else{
                    t = t->right;
                }
            }
        }






}
//treemap_get function:  Searches the tree for given 'key' and returns its associated
// value. Uses an ITERATIVE (loopy) search approach which starts a
// pointer at the root of the tree and changes it until the search key
// is found or determined not to be in the tree. If a matching key is
// found, returns a pointer to its value. If no matching key is found,
// returns NULL.

char *treemap_get(treemap_t *tree, char key[]){ //takes tree and key to look for in it
    node_t *temp = tree->root; // node that points at root of tree
    char *c = NULL; // pointer that will be assigned/returned
    while(temp != NULL){
        if(strcmp(temp->key,key) == 0){ //checks to see if current node's key is equal to the passed in key
        c = temp->val;
        break;
    } else if (strcmp(temp->key, key) > 0){ // checks to see if current node's key is greater than the key to look for
                                            //if so node is changed to left node of it
        temp = temp->left;
    } else if (strcmp(temp->key, key) < 0){ //checks to see if the current node's key is less then the given key.
        temp = temp->right;                 //if so, makes temp node will be pointed to the node to the right of it.
    }
    }
    return c;

}

// treemap_clear function: Eliminates all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes. Sets root node to null and
//size of the tree to 0.
void treemap_clear(treemap_t *tree){
    node_remove_all(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

// node_remove_all function: Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. First checks to see if the node is NULL, then
//traverses the left node and then the right node and then frees the current node.
void node_remove_all(node_t *cur){
    if(cur == NULL){
        return;
    }
    node_remove_all(cur->left); //traverses left nodes
    node_remove_all(cur->right); //traverses right nodes


    free(cur);
}

//treemap_print_revorder function: function that calls node_print_revorder
//to print the tree in reverse order. Passes into it the root of the tree
// and 0 as a starting indentation.

void treemap_print_revorder(treemap_t *tree){
    node_print_revorder(tree->root, 0);
}

// node_print_revorder function: Recursive helper function which prints all key/val pairs in the
// tree rooted at node 'cur' in reverse order. Traverses right
// subtree, prints cur node's key/val, then traverses left tree.
// Parameter 'indent' indicates how far to indent (2 spaces per indent
// level).

void node_print_revorder(node_t *cur, int indent){
    if(cur == NULL){ // checks if current node is null
        return;
    }
    node_print_revorder(cur->right, indent+1); //traverses right subtree

    for (int i = 0; i<indent; ++i){ //indents (adds spaces) by factors of two
        if(i %2 == 0){
           printf("  ");
        }

    }
    printf("%s -> %s\n", cur->key, cur->val); // prints keys and values

    node_print_revorder(cur->left, indent+1); //traverses left nodes

}

//treemap_print_preorder function: function that calls upon node_write_preorder helper function
//to print out tree in preorder. Inputs the root of the tree to being at, stdout
// as the file parameter, and 0 as the starting depth.

void treemap_print_preorder(treemap_t *tree){
    node_write_preorder(tree->root, stdout, 0);
}

// treemap_save function: function that saves the tree by opening the named file, writing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
void treemap_save(treemap_t *tree, char *fname){
    FILE *file;
    file = fopen(fname, "w"); // opens fname to write to
    node_write_preorder(tree->root, file, 0); //calls preorder helper function to write to file
    fclose(file);
}

// node_Write_preorder: aecursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.

void node_write_preorder(node_t *cur, FILE *out, int depth){
    if (cur == NULL){ // checks if node is null
            return;}
    for(int i = 0; i<depth; ++i){ // prints depth spaces to passed in file
        fprintf(out,"%s","  ");

        }
    fprintf(out,"%s %s\n", cur->key, cur->val); // prints key and values to passed in file
    node_write_preorder(cur->left, out, depth+1); // traverses left nodes
    node_write_preorder(cur->right, out, depth+1);//traverses right nodes
}

// treemap_load: function that clears the given tree then loads new elements to it from the
// named. Repeated calls to treemap_add() are used to add strings read
// from the file.  If the tree is stored in pre-order in the file, its
// exact structure will be restored.  Returns 1 if the tree is loaded
// successfully and 0 if opening the named file fails in which case no
// changes are made to the tree.

int treemap_load(treemap_t *tree, char *fname ){
    char key[128]; //array of keys
    char val[128]; //array of vals
    FILE *file;
    file = fopen(fname, "r");
    if(file == NULL){ //checks if the file is NULL
            printf("ERROR: could not open file '%s'\n", fname);
            return 0;

    }
     treemap_clear(tree); //clears tree

    while(fscanf(file, "%s %s", key, val) != EOF){ //while the file still has contents, add it to the respective arrays
                                                    //and then calls the add function to add them to the tree.
          treemap_add(tree, key, val);
          }
    fclose(file);

    return 1;
    }



