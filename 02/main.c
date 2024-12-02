#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int rep[64];
    int size;
} Report;

int eval_report(Report report, const int max_diff)
{
    int last = report.rep[0];
    int increasing = (report.rep[0] - report.rep[1]) > 0;
    for (int i = 1; i < report.size; i++)
    {
        int diff = report.rep[last] - report.rep[i];

        if (diff > 0 != increasing)
        {
            printf("Direction doesn't match. \n");
            return 0;
        }

        if (abs(diff) >= max_diff)
        {
            printf("Difference is too big. \n");
            return 0;
        }
    }

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
            cursor++;
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
        safe_count += eval_report(reports[i], 3);
    }

    return safe_count;
}

int main()
{
    Report rbuffer[2000];
    int r_count = parse_input("test_input.txt", rbuffer);

    printf("%d\n", r_count);
    printf("%d\n", part_1(rbuffer, r_count));

    return 0;
}
