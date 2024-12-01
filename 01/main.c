#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int value_a[1000];
    int value_b[1000];

    // File open
    FILE *fptr;
    fptr = fopen("input.txt", "r");

    char line[100];
    int counter = 0;
    while (fscanf(fptr, "%d", &value_a[counter]) == 1)
    {
        fscanf(fptr, "%d", &value_b[counter]);
        counter++;
    }

    // File close
    fclose(fptr);

    //printf("lines read: %d\n", counter);

    qsort(value_a, counter, sizeof(int), compare);
    qsort(value_b, counter, sizeof(int), compare);

    int sum = 0;
    for (int i = 0; i < counter; i++)
    {
        //printf("%d, ", value_a[i]);
        //printf("%d, ", value_b[i]);
        int diff;
        if (value_a[i] > value_b[i])
        {
            diff = value_a[i] - value_b[i];
        }
        else
        {
            diff = value_b[i] - value_a[i];
        }

        //printf("%d\n", diff);

        sum += diff;
    }

    // part 1
    printf("%d\n", sum);

    int similarity = 0;
    int count;
    for (int i = 0; i < counter; i++) {
        count = 0;
        for(int j = 0; j < counter; j++) {
            if(value_b[j] > value_a[i] ){
                    break;
            }
            else if (value_a[i] == value_b[j]) {
                count++;
            }
        }

        similarity += (value_a[i] * count);
    }

    // part 2
    printf("%d\n", similarity);

    return 0;
}
