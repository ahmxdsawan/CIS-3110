/*
Ahmad Sawan
1205875
Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

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

void badCharFunction(char *pattern, int patternLen, int *badChar)
{
    int i;
    for (i = 0; i < 256; i++){
        badChar[i] = -1;
    }
    for (i = 0; i < patternLen; i++){
        badChar[(int)pattern[i]] = i;
    }
}

void search(char *text, char *pattern, int *count, int *shifts){

    int textLen = strlen(text);
    int patternLen = strlen(pattern);
    int badChar[256];
    int shift = 0;


    badCharFunction(pattern, patternLen, badChar);
    
    while (shift <= textLen - patternLen){
        int j = patternLen - 1;

        while (j >= 0 && pattern[j] == text[shift + j]){
            j--;
        }
        if (j < 0){
            (*count)++;
            shift += (shift + patternLen < textLen) ? patternLen - badChar[(int)text[shift + patternLen]] : 1;
        }
        else{
            shift += max(1, j - badChar[(int)text[shift + j]]);

        }
        (*shifts)++;
    }
}

int main(){

    char *text;
    char pattern[100];
    int count = 0;
    int shifts = 0;
    clock_t start, end;

    text = readFile("data_A3_Q2.txt");

    printf("\nProgram for string search using Boyer-Moore algorithm\n");
    printf("Enter a pattern: ");
    scanf("%s", pattern);



    start = clock();
    search(text, pattern, &count, &shifts);
    end = clock();

    double duration = (((double)end - start) / CLOCKS_PER_SEC) * 1000;
    
    printf("Count: %d\n", count);
    printf("Shifts: %d\n", shifts);
    printf("Execution time = %.0f ms\n", duration);

    return 0;
}
