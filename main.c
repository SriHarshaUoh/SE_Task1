#include "student.h"

int main()
{
    Student students[MAX_STUDENTS];
    int count;

    count = readStudentData("students.txt", students);

    if (count == 0) {
        printf("No valid student records found.\n");
        return 0;
    }

    writeReport("result.txt", students, count);

    printf("Result file generated successfully.\n");
    return 0;
}
