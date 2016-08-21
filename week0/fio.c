#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INFILE_NAME "master.txt"
#define NUM_SUBJECTS 5
#define MAX_STR_LEN 256
#define MAX_NAME_LEN 16

typedef struct _student {
	int roll_no;

	// The name
	char first_name[MAX_NAME_LEN];
	char last_name[MAX_NAME_LEN];

	// The student's marks and their associated grades
	char grades[NUM_SUBJECTS];
	int marks[NUM_SUBJECTS];
} student;

// Prettily print the student
void print_student (student s, char **subjects, int *max);

int main()
{
	// Open the file
	FILE *infile = fopen(INFILE_NAME, "r");
	if (!infile) {
		printf("Can't open file, quitting!\n");
		return 1;
	}

	// Get the desired roll number from the user
	int desired_rn;
	printf("Enter the roll number of the student : ");
	scanf("%d", &desired_rn);

	// Used to keep track of current students and subjects
	student desired_student;
	int max_marks[NUM_SUBJECTS];
	char *subjects[NUM_SUBJECTS];

	// initialize subjects
	int i;
	for (i = 0; i < NUM_SUBJECTS; i++) {
		subjects[i] = malloc (MAX_NAME_LEN * sizeof(*subjects[i]));
	}

	// While file has not ended
	while (!feof(infile)) {
		// Get the subjects and their max marks
		int i;
		for (i = 0; i < NUM_SUBJECTS; i++) {
			fscanf(infile, "%d %s ", &max_marks[i], subjects[i]);
		}

		// Get the current roll number
		int current_rn = 0;
		fscanf(infile, "%d", &current_rn);

		// store the student's name and roll number
		desired_student.roll_no = current_rn;
		fscanf(infile, "%s %s", desired_student.first_name, desired_student.last_name);

		// Store the user's marks and grades
		for (i = 0; i < NUM_SUBJECTS; i++) {
			fscanf(infile, "%d %c ", &desired_student.marks[i], &desired_student.grades[i]);
		}

		// If we've found the right student, break!
		if (desired_rn == current_rn) {
			break;
		}
	}

	// Prettily print the student
	print_student(desired_student, subjects, max_marks);

	// Free used memory
	for (i = 0; i < NUM_SUBJECTS; i++) {
		free(subjects[i]);
	}

	return 0;
}

void print_student(student s, char **subjects, int *max)
{
	// calculate total marks
	int total = 0;
	int i;
	for (i = 0; i < NUM_SUBJECTS; i++) {
		total += max[i];
	}

	// calculate obtained marks
	int obtained = 0;
	for (i = 0; i < NUM_SUBJECTS; i++) {
		obtained += s.marks[i];
	}

	// calculate percentage
	float percentage = 100.0f * (double) obtained / (double) total;

	// Prettily print the result sheet's beginning
	printf("                        Indian Institute of Technology Mandi\n");
	printf("                         Academic Session : (Aug-Dec) 2016\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Name of the Student : %s %s\n", s.first_name, s.last_name);
	printf("Roll Number         : %d\n", s.roll_no);
	printf("--------------------------------------------------------------------------------\n");
	printf("Sr. No |    Subject Code    |    Maximum    |   Marks Obtained   |     Grade\n");
	printf("--------------------------------------------------------------------------------\n");

	// print the lines with the grades and the marks
	for (i = 0; i < NUM_SUBJECTS; i++) {
		printf("  [%d] %15s%18d%16d%20c\n", i + 1, subjects[i], 100, s.marks[i], s.grades[i]);
	}
	printf("--------------------------------------------------------------------------------\n");
	printf("                            Total %5d     Total %5d\n\n", obtained, total);

	// Find and store the division string
	char *division = malloc(128 * sizeof(*division));
	if (percentage > 60) {
		strcpy(division, "Student has passed with First division");
	} else if (percentage > 45) {
		strcpy(division, "Student has passed with Second division");
	} else {
		strcpy(division, "Student has failed.");
	}

	// print final percentage and result
	printf("                       Percentage %5.0f%%  %s\n", percentage, division);
	printf("--------------------------------------------------------------------------------\n");

	// Free used memory
	free(division);
}
