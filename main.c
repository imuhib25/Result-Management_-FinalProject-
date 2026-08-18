//Name: Intisar Muhib
//Student ID: 2026-2-60-239

#include <stdio.h>

struct studentData
{
    int s_ID;
    char name[100];
    float gpa_CSE103, gpa_MAT101, gpa_ENG7101, t_CGPA;
};

float calculateCGPA(float cse103, float mat101, float eng101)
{
    float cseCredit = 4.5;
    float matCredit = 3.0;
    float engCredit = 3.0;

    return ((cse103 * cseCredit) +
            (mat101 * matCredit) +
            (eng101 * engCredit)) / 10.5;
}

int main()
{
    FILE *inputFile, *outputFile;
    struct studentData stdList[100];

    int n, i, count = 0;
    int success = 1;

    inputFile = fopen("student_input.txt", "r");

    if (inputFile == NULL)
    {
        printf("Error: Could not open student_input.txt\n");
        printf("Please make sure the input file exists.\n");
        return 1;
    }

    outputFile = fopen("output.txt", "w");

    if (outputFile == NULL)
    {
        printf("Error: Could not create output.txt\n");
        fclose(inputFile);
        return 1;
    }

    if (fscanf(inputFile, "%d", &n) != 1)
    {
        printf("Error: Invalid input file format.\n");
        success = 0;
    }

    if (success && (n < 1 || n > 100))
    {
        printf("Error: Number of students must be between 1 and 100.\n");
        success = 0;
    }

    if (success)
    {
        fprintf(outputFile, "------------------------------------------------------\n");
        fprintf(outputFile, "ID      Name      CSE103   MAT101   ENG7101   CGPA\n");
        fprintf(outputFile, "------------------------------------------------------\n");
    }

    for (i = 0; i < n && success; i++)
    {
        if (fscanf(inputFile, "%d", &stdList[i].s_ID) != 1)
        {
            printf("Error: Invalid student ID for student %d.\n", i + 1);
            success = 0;
            break;
        }

        fgetc(inputFile);

        if (fscanf(inputFile, "%[^\n]s", stdList[i].name) != 1)
        {
            printf("Error: Invalid student name for student %d.\n", i + 1);
            success = 0;
            break;
        }

        if (fscanf(inputFile, "%f", &stdList[i].gpa_CSE103) != 1 ||
            fscanf(inputFile, "%f", &stdList[i].gpa_MAT101) != 1 ||
            fscanf(inputFile, "%f", &stdList[i].gpa_ENG7101) != 1)
        {
            printf("Error: Invalid GPA data for student %d.\n", i + 1);
            success = 0;
            break;
        }

        if (stdList[i].gpa_CSE103 < 0.0 ||
            stdList[i].gpa_CSE103 > 4.0 ||
            stdList[i].gpa_MAT101 < 0.0 ||
            stdList[i].gpa_MAT101 > 4.0 ||
            stdList[i].gpa_ENG7101 < 0.0 ||
            stdList[i].gpa_ENG7101 > 4.0)
        {
            printf("Error: Invalid GPA found for student %d (%s).\n",
                   stdList[i].s_ID, stdList[i].name);

            printf("GPA of each course must be between 0.00 and 4.00.\n");

            success = 0;
            break;
        }

        stdList[i].t_CGPA = calculateCGPA(
            stdList[i].gpa_CSE103,
            stdList[i].gpa_MAT101,
            stdList[i].gpa_ENG7101
        );

        fprintf(outputFile,
                "%-7d %-10s %-8.2f %-8.2f %-8.2f %-8.2f\n",
                stdList[i].s_ID,
                stdList[i].name,
                stdList[i].gpa_CSE103,
                stdList[i].gpa_MAT101,
                stdList[i].gpa_ENG7101,
                stdList[i].t_CGPA);

        count++;
    }

    fclose(inputFile);
    fclose(outputFile);

    if (!success)
    {
        remove("output.txt");

        printf("\nGrade sheet was NOT generated successfully.\n");
        printf("Please fix the error in student_input.txt and try again.\n");

        return 1;
    }

    if (count == 0)
    {
        remove("output.txt");

        printf("No student records found.\n");
        printf("Grade sheet was NOT generated successfully.\n");

        return 1;
    }

    printf("\nAll student records processed successfully.\n");
    printf("Grade sheet successfully saved to output.txt\n");

    return 0;
}
