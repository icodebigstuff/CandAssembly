#include <stdio.h>
#include <stdlib.h>

// print_graph function: Prints a graph of the values in data which is an array of integers
// that has len elements. The max_height argument is the height in
// character rows that the maximum number data[] should be.

void print_graph(int *data, int len, int max_height){
    int i;
    int min = data[0];
    int max = data[0];
    for (i = 0; i< len; ++i){ //find min value in data array
        if (data[i] < min){
            min = data[i];
        }
    }

    for(i = 0; i<len; ++i){ //finds max value in data array
        if(data[i] > max){
            max = data[i];
        }
    }

    int range = max - min; //calculates range
    double units_per_height = ((double)range)/max_height; //calculates units_per_height
    printf("length: %d\n", len);
    printf("min: %d\n", min);
    printf("max: %d\n", max);
    printf("range: %d\n", (int) range);
    printf("max_height: %d\n", max_height);
    printf("units_per_height: %0.2f\n", units_per_height);

    printf("     "); //adds five spaces as an indent
    for (i = 0; i<len; ++i){ //loop that prints top axes
        if (i%5 == 0 || i==0){
            printf("+");
        }
        else{
            printf("-");
        }
    }
    printf("\n");
    for(int j=max_height; j>=0; --j){ //loop for main body

        int cutoff = (int) (min + j * units_per_height); //calculates cutoff
        printf("%3d |",(int) cutoff); //prints vertical axis & its values
        char *x = "X";
        for (int i=0; i<len; i++){ // loops prints data points (x's) and spaces
            if(data[i] >= cutoff){
                printf("%s", x);
            } else{
                printf(" ");
            }
        }
        printf("\n");




    }
    printf("     "); //five spaces as indentation
    for (i = 0; i<len; ++i){ //loop that prints lower axes
        if (i%5 == 0 || i==0){
            printf("+");
        }
        else{
            printf("-");
        }
    }

    printf("\n");
    printf("     "); //five spaces for indentation
    for(i =0; i<len; ++i){  //loop that prints x axis values
        if (i %5 == 0 || i== 0){
            printf("%-5d", i);
        }

    }





}
