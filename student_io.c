#include "student.h"
#include <stdlib.h>

int readStudentData(const char* fileName, Student students[])
{
    FILE* file = fopen(fileName, "r");
    int count = 0;

    if (!file) {
        printf("Error opening input file.\n");
        return 0;
    }

    while (count < MAX_STUDENTS) {

        Student temp;
        int status = fscanf(file,
            "%s %s %d %d %d %d %d",
            temp.studentId,
            temp.name,
            &temp.marks[0],
            &temp.marks[1],
            &temp.marks[2],
            &temp.marks[3],
            &temp.marks[4]);

        if (status != 7)
            break;

        if (!isValidRecord(&temp, students, count)) {
            printf("Record skipped\n\n");
            continue;
        }

        computeResults(&temp);
        students[count++] = temp;
    }

    fclose(file);
    return count;
}
