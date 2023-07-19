// Code ni Sir Enhanced.

#include <stdio.h>
#include <stdlib.h>

// Constants
#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 20
#define MAX_SUBJECTS 3

// Structure Definitions
struct Subject {
    int code;
    char name[MAX_NAME_LENGTH];
    int mark;
};

struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    struct Subject subjects[MAX_SUBJECTS];
    int total;
    float percentage;
};

// Function Declarations
void createStudentRecords();
void displayStudentRecords();
void appendStudentRecords();
int getNumberOfRecords();
void searchStudentRecord();
void updateStudentRecord();
void deleteStudentRecord();
void sortStudentsByTotalMarks();

// Main function - Driver Function
int main() {
    int choice;

    do {
        printf("\n[1] CREATE");
        printf("\n[2] DISPLAY");
        printf("\n[3] APPEND");
        printf("\n[4] NUMBER OF RECORDS");
        printf("\n[5] SEARCH A RECORD");
        printf("\n[6] UPDATE");
        printf("\n[7] DELETE");
        printf("\n[8] SORT");
        printf("\n[0] EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createStudentRecords();
                break;
            case 2:
                displayStudentRecords();
                break;
            case 3:
                appendStudentRecords();
                break;
            case 4:
                printf("\nNumber of records: %d\n", getNumberOfRecords());
                break;
            case 5:
                searchStudentRecord();
                break;
            case 6:
                updateStudentRecord();
                break;
            case 7:
                deleteStudentRecord();
                break;
            case 8:
                sortStudentsByTotalMarks();
                break;
            default:
                if (choice != 0)
                    printf("Invalid choice. Try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function Definitions
void createStudentRecords() {
    struct Student students[MAX_STUDENTS];
    int numStudents, i, j;

    printf("How many students you want to create?: ");
    scanf("%d", &numStudents);

    for (i = 0; i < numStudents; i++) {
        printf("Enter Roll Number: ");
        scanf("%d", &students[i].rollNumber);
        fflush(stdin);

        printf("Enter name: ");
        scanf(" %[^\n]s", students[i].name);

        students[i].total = 0;
        students[i].percentage = 0;

        for (j = 0; j < MAX_SUBJECTS; j++) {
            printf("Enter mark of subject %d: ", j + 1);
            scanf("%d", &students[i].subjects[j].mark);
            students[i].total += students[i].subjects[j].mark;
        }

        students[i].percentage = students[i].total / (float)MAX_SUBJECTS;
    }

    FILE *fp = fopen("record.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(students, sizeof(struct Student), numStudents, fp);
    fclose(fp);
}

void displayStudentRecords() {
    struct Student student;
    FILE *fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n%-5s%-20s%-5s%-5s%-5s%-8s", "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total");
    while (fread(&student, sizeof(struct Student), 1, fp)) {
        printf("\n%-5d%-20s", student.rollNumber, student.name);

        int j;
        for (j = 0; j < MAX_SUBJECTS; j++) {
            printf("%-5d", student.subjects[j].mark);
        }
        printf("%-5d%-8.2f", student.total, student.percentage);
    }

    fclose(fp);
}

void appendStudentRecords() {
    struct Student students[MAX_STUDENTS];
    int numStudents, i, j;

    printf("How many students you want to append?: ");
    scanf("%d", &numStudents);
    fflush(stdin);

    FILE *fp = fopen("record.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < numStudents; i++) {
        printf("Enter Roll Number: ");
        scanf("%d", &students[i].rollNumber);
        fflush(stdin);

        printf("Enter name: ");
        scanf(" %[^\n]s", students[i].name);

        students[i].total = 0;
        students[i].percentage = 0;

        for (j = 0; j < MAX_SUBJECTS; j++) {
            printf("Enter mark of subject %d: ", j + 1);
            scanf("%d", &students[i].subjects[j].mark);
            students[i].total += students[i].subjects[j].mark;
        }

        students[i].percentage = students[i].total / (float)MAX_SUBJECTS;
    }

    fwrite(students, sizeof(struct Student), numStudents, fp);
    fclose(fp);
}

int getNumberOfRecords() {
    FILE *fp = fopen("record.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    int numRecords = ftell(fp) / sizeof(struct Student);
    fclose(fp);

    return numRecords;
}

void searchStudentRecord() {
    struct Student student;
    FILE *fp = fopen("record.txt", "r");
    int rollNumber, found = 0;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number to search: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (student.rollNumber == rollNumber) {
            found = 1;
            printf("\n%-5d%-20s", student.rollNumber, student.name);

            int j;
            for (j = 0; j < MAX_SUBJECTS; j++) {
                printf("%-5d", student.subjects[j].mark);
            }

            printf("%-5d%-8.2f", student.total, student.percentage);
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nRecord not found\n");
    }
}

void updateStudentRecord() {
    struct Student student;
    FILE *fp = fopen("record.txt", "r");
    FILE *fpTemp = fopen("temp.txt", "w");
    int rollNumber, found = 0;

    if (fp == NULL || fpTemp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number to update: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (student.rollNumber == rollNumber) {
            found = 1;
            printf("Enter new name: ");
            scanf(" %[^\n]s", student.name);

            student.total = 0;
            student.percentage = 0;

            int j;
            for (j = 0; j < MAX_SUBJECTS; j++) {
                printf("Enter new mark of subject %d: ", j + 1);
                scanf("%d", &student.subjects[j].mark);
                student.total += student.subjects[j].mark;
            }

            student.percentage = student.total / (float)MAX_SUBJECTS;
        }

        fwrite(&student, sizeof(struct Student), 1, fpTemp);
    }

    fclose(fp);
    fclose(fpTemp);

    if (found) {
        fpTemp = fopen("temp.txt", "r");
        fp = fopen("record.txt", "w");

        while (fread(&student, sizeof(struct Student), 1, fpTemp)) {
            fwrite(&student, sizeof(struct Student), 1, fp);
        }

        fclose(fp);
        fclose(fpTemp);
    } else {
        printf("\nRecord not found\n");
    }
}

void deleteStudentRecord() {
    struct Student student;
    FILE *fp = fopen("record.txt", "r");
    FILE *fpTemp = fopen("temp.txt", "w");
    int rollNumber, found = 0;

    if (fp == NULL || fpTemp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter roll number to delete: ");
    scanf("%d", &rollNumber);

    while (fread(&student, sizeof(struct Student), 1, fp)) {
        if (student.rollNumber == rollNumber) {
            found = 1;
        } else {
            fwrite(&student, sizeof(struct Student), 1, fpTemp);
        }
    }

    fclose(fp);
    fclose(fpTemp);

    if (found) {
        fpTemp = fopen("temp.txt", "r");
        fp = fopen("record.txt", "w");

        while (fread(&student, sizeof(struct Student), 1, fpTemp)) {
            fwrite(&student, sizeof(struct Student), 1, fp);
        }

        fclose(fp);
        fclose(fpTemp);
    } else {
        printf("\nRecord not found\n");
    }
}

void sortStudentsByTotalMarks() {
    struct Student students[MAX_STUDENTS];
    FILE *fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fseek(fp, 0, SEEK_END);
    int numStudents = ftell(fp) / sizeof(struct Student);

    if (numStudents == 0) {
        printf("No records to sort.\n");
        fclose(fp);
        return;
    }

    rewind(fp);
    fread(students, sizeof(struct Student), numStudents, fp);
    fclose(fp);

    int i, j;
    struct Student temp;

    for (i = 0; i < numStudents; i++) {
        for (j = i + 1; j < numStudents; j++) {
            if (students[i].total < students[j].total) {
                temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }

    printf("\n%-5s%-20s%-5s%-5s%-5s%-8s", "Roll", "Name", "Sub1", "Sub2", "Sub3", "Total");

    for (i = 0; i < numStudents; i++) {
        printf("\n%-5d%-20s", students[i].rollNumber, students[i].name);

        for (j = 0; j < MAX_SUBJECTS; j++) {
            printf("%-5d", students[i].subjects[j].mark);
        }

        printf("%-5d%-8.2f", students[i].total, students[i].percentage);
    }
}
