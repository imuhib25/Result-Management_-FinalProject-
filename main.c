#include <stdio.h>
struct studentData
{
    int s_ID;
    char name[100];
    float gpa_CSE103, gpa_MAT101, gpa_ENG7101, t_CGPA;
};

int main()
{
    FILE *ptr1, *ptr2;
    struct studentData stdList[100];
    ptr1 = fopen("input1.txt", "r");
    ptr2 = fopen("output1.txt", "w");
    int n, i;
    fscanf(ptr1, "%d", &n);

    for (i = 0; i < n; i++)
    {
        fscanf(ptr1, "%d", &stdList[i].s_ID);
        fgetc(ptr1);
        fscanf(ptr1, "%[^\n]s", stdList[i].name);
        fscanf(ptr1, "%f", &stdList[i].gpa_CSE103);
        fscanf(ptr1, "%f", &stdList[i].gpa_MAT101);
        fscanf(ptr1, "%f", &stdList[i].gpa_ENG7101);
        stdList[i].t_CGPA = ((stdList[i].gpa_CSE103 * 4.5) 
        + (stdList[i].gpa_ENG7101 * 3) 
        + (stdList[i].gpa_MAT101 * 3)) / 10.5;
        fprintf(ptr2, "Serial: %d Student ID: %d, Name: %s, GPA in CSE103, MAT101, ENG7101: %.2f, %.2f, %.2f, Calculated CGPA: %.2f\n", 
            i+1, stdList[i].s_ID, stdList[i].name, stdList[i].gpa_CSE103, stdList[i].gpa_MAT101, stdList[i].gpa_ENG7101, stdList[i].t_CGPA);
    }
    fclose(ptr1);
    fclose(ptr2);
    return 0;
}
