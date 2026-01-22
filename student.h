#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>

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

/* File Handling */
int readStudentData(const char* fileName, Student students[]);

/* Validation */
int isValidRecord(const Student* student,
                  const Student students[],
                  int count);

/* Processing */
void computeResults(Student* student);
char calculateGrade(float percentage);

/* Reporting */
void writeReport(const char* fileName,
                 const Student students[],
                 int count);
void writeStatistics(FILE* file,
                     const Student students[],
                     int count);

#endif
