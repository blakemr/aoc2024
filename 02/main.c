#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rep[64];
    int size;
} Report;

int eval_report(Report report, const int max_diff, int err_tolerance)
{
    int increasing = (report.rep[0] - report.rep[1]) > 0;
    int err_count = 0;
    
    for (int i = 1; i < report.size; i++)
    {
        int diff = report.rep[i-1] - report.rep[i];

        if (diff > 0 != increasing) {
            err_count++;
        }

        else if (abs(diff) > max_diff || diff == 0) {
            err_count++;
        }

        if (err_count > err_tolerance) {
            /*
            printf(" Fail\t");

            for (int i = 0; i < report.size; i++) {
                printf("%d, ", report.rep[i]);
            }

            printf("\n");
            */
            return 0;
        }

    }

    /*
    printf(" Pass\t");

    for (int i = 0; i < report.size; i++) {
        printf("%d, ", report.rep[i]);
    }

    printf("\n");
    */

    return 1;
}

int parse_input(const char path[], Report reports[])
{
    // File open
    FILE *fptr;
    fptr = fopen(path, "r");

    char line[256];
    int report_count = 0;
    while (fgets(line, sizeof(line), fptr))
    {
        Report new_report = {
            .rep = {},
            .size = 0,
        };

        int n;
        char* cursor = line;

        while (sscanf(cursor, "%d", &n) == 1)
        {
            new_report.rep[new_report.size] = n;
            new_report.size++;

            // skip spaces, and multi-digit numbers
            while (*cursor != ' ' && cursor) cursor++;
            cursor++;
        }

        // reset line data
        for(int i = 0; i < sizeof(line); i++) {
            line[i] = 0;
        }

        reports[report_count] = new_report;

        report_count++;
    }

    // File close
    fclose(fptr);

    return report_count;
}

int part_1(Report reports[], int size) {
    int safe_count = 0;
    for(int i=0; i<size; i++) {
        safe_count += eval_report(reports[i], 3, 0);
    }

    return safe_count;
}

int part_2(Report reports[], int size) {
    int safe_count = 0;
    for(int i=0; i<size; i++) {
        safe_count += eval_report(reports[i], 3, 1);
    }

    return safe_count;  
}

int main()
{
    Report rbuffer[2000];
    int r_count = parse_input("input.txt", rbuffer);

    printf("%d\n", r_count);
    printf("%d\n", part_1(rbuffer, r_count));
    printf("%d\n", part_2(rbuffer, r_count));

    return 0;
}
