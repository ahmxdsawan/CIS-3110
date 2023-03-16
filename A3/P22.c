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



char *readFile(char *filename)
{
    int i = 0;
    char *str = NULL;
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("File Error");
        return NULL;
    }
    while (!feof(file))
    {
        if (str == NULL)
        {
            str = malloc(sizeof(char));
            str[i] = fgetc(file);
        }
        else
        {
            str = realloc(str, sizeof(char) * (count + 1));
            str[i] = fgetc(file);
        }
        count++;
        i++;
    }
    str[count - 1] = '\0';
    fclose(file);

    return str;
}



int main()
{

    clock_t start, end;
    char pattern[1000];
    int count = 0;
    int shifts = 0;
    char *string;

    string = readFile("data_A3_Q2.txt");

    printf("Enter pattern to search: ");
    scanf("%s", pattern);
    printf("\nProgram for string search using Horspool's algorithim\n");


    int sTable[1000];
    int len = strlen(string);


   
    int sLen = strlen(pattern) - 1;
    int sIndex = sLen - 1;

    start = clock();

    for (int i = 0; i < 1000; i++){
        sTable[i] = sLen;
    }

    for (int i = 0; i < sIndex; i++){
        int charIndex = pattern[i];
        sTable[charIndex] = sIndex - i;
    }

    int shift = sIndex;
    while (shift < len){
        int patternIndex = 0;
        while (patternIndex <= sIndex && pattern[sIndex - patternIndex] == string[shift - patternIndex])
        {
            patternIndex++;
        }
        int shiftIndex = string[shift];
        if (patternIndex == sLen)
        {
            count++;
            int max = shift + sLen;
            if (max > len){
                shift += 1;
            }
            else{
                shift += sLen;
            }
        }
        else{
            shift += sTable[shiftIndex];
        }
        shifts++;
    }

    end = clock();

    double duration = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    printf("Total number of occurrences found: %d\n", count);
    printf("Total number of pattern shifts: %d\n", shifts);
    printf("Total running time: %.0lf ms\n", duration);



    return 0;
}
