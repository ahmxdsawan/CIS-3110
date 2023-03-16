/*
Ahmad Sawan 
1205875
Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

int main() {

    clock_t start, end;
    char text[1000], pattern[1000];
    char *result;
    int count = 0;
    int shifts = 0;


    FILE *file = fopen("data_A3_Q2.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }



    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    start = clock();


    while (fscanf(file, "%s", text) != EOF) {
        

        result = strstr(text, pattern);

        if(result != NULL){
            count++;
        }
        shifts++;
    }
    end = clock();

    double duration = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    printf("A Brute force program for string search.\n");
    printf("Total number of occurrences found: %d\n", count);
    printf("Total number of pattern shifts: %d\n", shifts * 4);
    printf("Execution time = %.0lf ms\n", duration);

    fclose(file);

    return 0;
}
