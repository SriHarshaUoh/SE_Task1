#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define SUBJECT_COUNT 5
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 20

typedef struct {
    char studentId[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    int marks[SUBJECT_COUNT];
    int totalMarks;
    float percentage;
    float cgpa;
    char grade;
} Student;

int Student_Details(const char* fileName, Student students[]);
int IsValid_Record(const Student* student, const Student students[], int count);
void ComputeResults(Student* student);
char CalculateGrade(float percentage);
void WriteReport(const char* fileName, const Student students[], int count);
void WriteStats(FILE* file, const Student students[], int count);


int main()
{
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    studentCount = Student_Details("students.txt", students);
    if (studentCount == 0) {
        printf("No valid student records found.\n");
        return 0;
    }
    WriteReport("result.txt",students, studentCount);
    return 0;
}

int Student_Details(const char* fileName, Student students[])
{
    FILE* file = fopen(fileName, "r");
    int count = 0;
    if (file == NULL) {
        printf("Error: Unable to open input file.\n");
        return 0;
    }
    while (!feof(file) && count < MAX_STUDENTS) {
        Student tempStudent;
        int readCount;
        readCount = fscanf(
            file,
            "%s %s %d %d %d %d %d",
            tempStudent.studentId,
            tempStudent.name,
            &tempStudent.marks[0],
            &tempStudent.marks[1],
            &tempStudent.marks[2],
            &tempStudent.marks[3],
            &tempStudent.marks[4]
        );

        if (readCount != 7) {
            break;
        }

        if (!IsValid_Record(&tempStudent, students, count)) {
    printf("(Record skipped)\n\n");
    continue;}
        ComputeResults(&tempStudent);
        students[count] = tempStudent;
        count++;
    }

    fclose(file);
    return count;
}

int IsValid_Record(const Student* student, const Student students[], int count)
{
    int i;
    for (i = 0; student->studentId[i] != '\0'; i++) {
        if (!isalnum(student->studentId[i])) {
            printf("Invalid Student ID: %s\n", student->studentId);
            return 0;
        }
    }
    for (i = 0; i < count; i++) {
        if (strcmp(student->studentId, students[i].studentId) == 0) {
            printf("Duplicate Student ID: %s\n", student->studentId);
            return 0;
        }
    }
    for (i = 0; student->name[i] != '\0'; i++) {
        if (!isalpha(student->name[i])) {
            printf("Invalid Name: %s\n", student->name);
            return 0;
        }
    }
    for (i = 0; i < SUBJECT_COUNT; i++) {
        if (student->marks[i] < 0 || student->marks[i] > 100) {
            printf("Invalid marks for Student ID: %s\n", student->studentId);
            return 0;
        }
    }

    return 1;
}

void ComputeResults(Student* student)
{
    int i;
    int total = 0;

    for (i = 0; i < SUBJECT_COUNT; i++) {
        total += student->marks[i];
    }

    student->totalMarks = total;
    student->percentage = total / (float)SUBJECT_COUNT;
    student->cgpa = student->percentage / 10.0f;
    student->grade = CalculateGrade(student->percentage);
}

char CalculateGrade(float percentage)
{
    if (percentage >= 90) return 'O';
    if (percentage >= 85) return 'A';
    if (percentage >= 75) return 'B';
    if (percentage >= 65) return 'C';
    if (percentage >= 60) return 'D';
    if (percentage >= 55) return 'E';
    if (percentage >= 50) return 'P';

    return 'F';
} 

void WriteReport(const char* fileName, const Student students[], int count)
{
    FILE* file = fopen(fileName, "w");
    int i, j;

    if (file == NULL) {
        printf("Error: Unable to create output file.\n");
        return;
    }

    fprintf(file, "STUDENT RESULT REPORT\n");
   
    fprintf(file, "%-10s %-15s ", "ID", "Name");
    for (j = 0; j < SUBJECT_COUNT; j++) {
        fprintf(file, "M%d ", j + 1);
    }
    fprintf(file, " Total  %%   Grade  CGPA\n");
    fprintf(file, "\n");

    for (i = 0; i < count; i++) {
        fprintf(file, "%-10s %-15s ",
                students[i].studentId,
                students[i].name);

        for (j = 0; j < SUBJECT_COUNT; j++) {
            fprintf(file, "%3d ", students[i].marks[j]);
        }

        fprintf(file, "%5d %6.2f   %c     %4.2f\n",
                students[i].totalMarks,
                students[i].percentage,
                students[i].grade,
                students[i].cgpa);
    }

    WriteStats(file, students, count);

    fclose(file);
}

void WriteStats(FILE* file, const Student students[], int count)
{
    int i;
    float totalPercentage = 0.0f;
    float highest = students[0].percentage;
    float lowest = students[0].percentage;
    int gradeCount[8] = {0};

    for (i = 0; i < count; i++) {
        totalPercentage += students[i].percentage;

        if (students[i].percentage > highest) {
            highest = students[i].percentage;
        }

        if (students[i].percentage < lowest) {
            lowest = students[i].percentage;
        }

        switch (students[i].grade) {
            case 'O': gradeCount[0]++; break;
            case 'A': gradeCount[1]++; break;
            case 'B': gradeCount[2]++; break;
            case 'C': gradeCount[3]++; break;
            case 'D': gradeCount[4]++; break;
            case 'E': gradeCount[5]++; break;
            case 'P': gradeCount[6]++; break;
            case 'F': gradeCount[7]++; break;
        }
    }

    fprintf(file, "\nCLASS STATISTICS\n");
    fprintf(file, "\n");
    fprintf(file, "Class Average Percentage : %.2f\n", totalPercentage / count);
    fprintf(file, "Highest Percentage       : %.2f\n", highest);
    fprintf(file, "Lowest Percentage        : %.2f\n", lowest);

    fprintf(file, "\nGrade Distribution:\n");
    fprintf(file, "O : %d\n", gradeCount[0]);
    fprintf(file, "A : %d\n", gradeCount[1]);
    fprintf(file, "B : %d\n", gradeCount[2]);
    fprintf(file, "C : %d\n", gradeCount[3]);
    fprintf(file, "D : %d\n", gradeCount[4]);
    fprintf(file, "E : %d\n", gradeCount[5]);
    fprintf(file, "P : %d\n", gradeCount[6]);
    fprintf(file, "F : %d\n", gradeCount[7]);
}
