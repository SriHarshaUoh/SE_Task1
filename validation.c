#include "student.h"
#include <string.h>
#include <ctype.h>

int isValidRecord(const Student* student,
                  const Student students[],
                  int count)
{
    int i;

    for (i = 0; student->studentId[i]; i++)
        if (!isalnum(student->studentId[i])) {
            printf("Invalid ID: %s\n", student->studentId);
            return 0;
        }

    for (i = 0; i < count; i++)
        if (strcmp(student->studentId,
                   students[i].studentId) == 0) {
            printf("Duplicate ID: %s\n",
                    student->studentId);
            return 0;
        }

    for (i = 0; student->name[i]; i++)
        if (!isalpha(student->name[i])) {
            printf("Invalid Name: %s\n",
                    student->name);
            return 0;
        }

    for (i = 0; i < SUBJECT_COUNT; i++)
        if (student->marks[i] < 0 ||
            student->marks[i] > 100) {
            printf("Invalid marks for %s\n",
                    student->studentId);
            return 0;
        }

    return 1;
}
