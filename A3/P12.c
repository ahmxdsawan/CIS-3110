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

void MergeSortMod(int *data, int *tempD, int left, int right);

void Merge(int *data, int *tempD, int left, int middle, int right);

int main()
{

    char filename[cMaxFILELENGTH];
    int num_Intervals = 0;
    int cPoints = 0;
    int i = 0;
    clock_t start, end;


    int *tempx = (int *)malloc(sizeof(int) * 30000);
    int *tempy = (int *)malloc(sizeof(int) * 30000);

    int *tempdata1 = (int *)malloc(sizeof(int) * 30000);
    int *tempdata2 = (int *)malloc(sizeof(int) * 30000);

    


    printf("Please input the file name: ");
    scanf("%s", filename);

    FILE *fp;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    while (!feof(fp) && i < 30000)
    {
        fscanf(fp, "%d %d", &tempx[i], &tempy[i]);
        i++;
    }

    MergeSortMod(tempx, tempdata1, 0, 30000 - 1);
    MergeSortMod(tempy, tempdata2, 0, 30000 - 1);



    start = clock();

    i = 1;
    int j = 0;
    int tempC = 0;
    while (i < 30000 && j < 30000){
        if (tempx[i] < tempy[j]){
            tempC++;
            if (tempC > num_Intervals){
                num_Intervals = tempC;
                cPoints = tempx[i] + 1; 
            }
            i++;
        }
        else if (tempx[i] == tempy[j]){
            j++;
            i++;
        }
        else{
            tempC--;
            j++;
        }
    }

    end = clock();


    fclose(fp);


    double duration = (((double)end - start) / CLOCKS_PER_SEC) * 1000;

    printf("\nBrute force program for finding max number of intervals\n");
    printf("The maximum number of intervals: %d\n", num_Intervals);
    printf("The intervals include point: %d\n", cPoints);
    printf("Time for finding the maximum number: %.0lf ms\n\n", duration);

    return 0;
}


void MergeSortMod(int *data, int *tempD, int left, int right)
{
    int middle;

    if (right > left){
        middle = (right + left) / 2;
        MergeSortMod(data, tempD, left, middle);
        MergeSortMod(data, tempD, middle + 1, right);
        Merge(data, tempD, left, middle + 1, right);
    }
}

void Merge(int *data, int *tempD, int left, int middle, int right)
{
    int mIndex = left;
    int arrayL = left;
    int arrayR = middle;
    while ((arrayL <= middle - 1) && (arrayR <= right)){
        if (data[arrayL] <= data[arrayR]){
            tempD[mIndex++] = data[arrayL++];
        }
        else{
            tempD[mIndex++] = data[arrayR++];
        }
    }

    while (arrayL <= (middle - 1)){
        tempD[mIndex++] = data[arrayL++];
    }
    while (arrayR <= right){
        tempD[mIndex++] = data[arrayR++];
    }
    for (arrayL = left; arrayL <= right; arrayL++){
        data[arrayL] = tempD[arrayL];
    }
}
