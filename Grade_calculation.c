#include "student.h"

void computeResults(Student* student)
{
    int i, sum = 0;

    for (i = 0; i < SUBJECT_COUNT; i++)
        sum += student->marks[i];

    student->totalMarks = sum;
    student->percentage = sum / (float)SUBJECT_COUNT;
    student->cgpa = student->percentage / 10;
    student->grade = calculateGrade(student->percentage);
}

char calculateGrade(float p)
{
    if (p >= 90) return 'O';
    if (p >= 85) return 'A';
    if (p >= 75) return 'B';
    if (p >= 65) return 'C';
    if (p >= 60) return 'D';
    if (p >= 55) return 'E';
    if (p >= 50) return 'P';
    return 'F';
}
