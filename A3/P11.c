/*
Ahmad Sawan 
1205875
Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define cMaxFILELENGTH 1000

int main()
{

    char filename[cMaxFILELENGTH];
    int num_Intervals = 0;
    int cPoints = 0;
    int i = 0;
    clock_t start, end;

    printf("Please input the file name: ");
    scanf("%s", filename);

    int array[30000][2];
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (!feof(fp) && i < 30000)
    {
        fscanf(fp, "%d %d", &array[i][0], &array[i][1]);
        i++;
    }

    fclose(fp);

    int cMin = array[0][0];
    int cMax = array[0][1];

    start = clock();
    for (i = 0; i < 30000; i++)
    {

        if (array[i][0] < cMin)
        {
            cMin = array[i][0];
        }
        if (array[i][1] > cMax)
        {
            cMax = array[i][1];
        }
    }

    for (int i = cMin + 1; i < cMax; i++)
    {
        int tempCount = 0;
        for (int j = 0; j < 30000; j++)
        {
            if (array[j][0] < i && array[j][1] > i)
            {
                tempCount++;
            }
        }
        if (tempCount > num_Intervals)
        {
            num_Intervals = tempCount;
            cPoints = i;
        }
    }
    end = clock();

    double duration = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\nBrute force program for finding max number of intervals\n");
    printf("The maximum number of intervals: %d\n", num_Intervals);
    printf("The intervals include point: %d\n", cPoints);
    printf("Time for finding the maximum number: %.0lf ms\n\n", duration);

    return 0;
}
