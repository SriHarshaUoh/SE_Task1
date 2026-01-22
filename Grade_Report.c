#include "student.h"

void writeReport(const char* fileName,
                 const Student students[],
                 int count)
{
    FILE* file = fopen(fileName, "w");
    int i, j;

    if (!file) {
        printf("Unable to create output file\n");
        return;
    }

    fprintf(file, "STUDENT RESULT REPORT\n\n");

    fprintf(file, "%-10s %-15s ", "ID", "Name");
    for (j = 0; j < SUBJECT_COUNT; j++)
        fprintf(file, "M%d ", j + 1);

    fprintf(file, "Total %% Grade CGPA\n\n");

    for (i = 0; i < count; i++) {

        fprintf(file, "%-10s %-15s ",
                students[i].studentId,
                students[i].name);

        for (j = 0; j < SUBJECT_COUNT; j++)
            fprintf(file, "%3d ",
                    students[i].marks[j]);

        fprintf(file, "%5d %6.2f %3c %5.2f\n",
                students[i].totalMarks,
                students[i].percentage,
                students[i].grade,
                students[i].cgpa);
    }

    writeStatistics(file, students, count);
    fclose(file);
}
void writeStatistics(FILE* file,
                     const Student students[],
                     int count)
{
    int i;
    float sum = 0;
    float high = students[0].percentage;
    float low  = students[0].percentage;
    int grades[8] = {0};

    for (i = 0; i < count; i++) {

        sum += students[i].percentage;

        if (students[i].percentage > high)
            high = students[i].percentage;

        if (students[i].percentage < low)
            low = students[i].percentage;

        switch (students[i].grade) {
            case 'O': grades[0]++; break;
            case 'A': grades[1]++; break;
            case 'B': grades[2]++; break;
            case 'C': grades[3]++; break;
            case 'D': grades[4]++; break;
            case 'E': grades[5]++; break;
            case 'P': grades[6]++; break;
            case 'F': grades[7]++; break;
        }
    }

    fprintf(file, "\nCLASS STATISTICS\n\n");
    fprintf(file, "Average : %.2f\n", sum/count);
    fprintf(file, "Highest : %.2f\n", high);
    fprintf(file, "Lowest  : %.2f\n\n", low);

    char gradeNames[] = {'O','A','B','C','D','E','P','F'};

    for (i = 0; i < 8; i++)
        fprintf(file, "%c : %d\n",
                gradeNames[i], grades[i]);
}
