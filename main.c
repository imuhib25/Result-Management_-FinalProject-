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
    return ((cse103 * cseCredit) + (mat101 * matCredit) + (eng101 * engCredit)) / 10.5;
}

int main()
{
    FILE *inputFile, *outputFile;
    struct studentData stdList[100];
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
        return 0;
    }
    fprintf(outputFile, "------------------------------------------------------\n");
    fprintf(outputFile,"ID      Name      CSE103   MAT101   ENG101    CGPA\n");
    fprintf(outputFile,"-------------------------------------------------------\n");
    int n, i, count = 0;
    fscanf(inputFile, "%d", &n);

    for (i = 0; i < n; i++)
    {
        count++;
        fscanf(inputFile, "%d", &stdList[i].s_ID);
        fgetc(inputFile);
        fscanf(inputFile, "%[^\n]s", stdList[i].name);
        fscanf(inputFile, "%f", &stdList[i].gpa_CSE103);
        fscanf(inputFile, "%f", &stdList[i].gpa_MAT101);
        fscanf(inputFile, "%f", &stdList[i].gpa_ENG7101);
        if (stdList[i].gpa_CSE103 > 4.00 || stdList[i].gpa_MAT101 > 4.00 || stdList[i].gpa_ENG7101 > 4.00)
        {
            printf("Invalid data found! GPA of each courses should be equal or less than 4.00");
            return 0;
        }

        stdList[i].t_CGPA = calculateCGPA(stdList[i].gpa_CSE103, stdList[i].gpa_MAT101, stdList[i].gpa_ENG7101);
        fprintf(outputFile,"%-7d %-10s %-8.2f %-8.2f %-8.2f %-8.2f\n",
        stdList[i].s_ID, stdList[i].name, stdList[i].gpa_CSE103, stdList[i].gpa_MAT101, stdList[i].gpa_ENG7101, stdList[i].t_CGPA);
    }
    if (count == 0)
    {
        printf("No student records found.\n");
        return 0;
    }
    fclose(inputFile);
    printf("\nGrade sheet successfully saved to output.txt\n");
    fclose(outputFile);
    return 0;
}
