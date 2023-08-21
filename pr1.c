#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

struct Employee
{
    int id;
    char name[50];
    char mobile[15];
    float salary;
};

void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}

void createRecord(FILE *fp)
{
    struct Employee emp;
    printf("ENTER ID OF EMPLOYEE: ");
    scanf("%d", &emp.id);
    clearInputBuffer();
    printf("ENTER NAME OF EMPLOYEE: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strlen(emp.name) - 1] = '\0'; // Remove newline character
    printf("ENTER MOBILE NO. OF EMPLOYEE: ");
    scanf("%s", emp.mobile);
    printf("ENTER SALARY OF EMPLOYEE: ");
    scanf("%f", &emp.salary);
    fprintf(fp, " %d \t\t%s \t\t %s \t %.2f\n", emp.id, emp.name, emp.mobile, emp.salary);
}

void viewRecords(FILE *fp)
{
    char c;
    while ((c = fgetc(fp)) != EOF)
    {
        printf("%c", c);
    }
}

int main()
{
    char fname[50];
    printf("ENTER ADDRESS BOOK NAME: ");
    scanf("%s", fname);
    FILE *fp = fopen(fname, "a+");
    fprintf(fp, "ID \t\t NAME\t\t MOB_NO\t\t SALARY\n");

    int choice;
    while (1)
    {
        printf("******ADDRESS BOOK****** :\n");
        printf("\t1.CREATE ADDRESS BOOK\n");
        printf("\t2.VIEW ADDRESS BOOK\n");
        printf("\t3.INSERT A RECORD\n");
        printf("\t4.DELETE A RECORD\n");
        printf("\t5.MODIFY A RECORD\n");
        printf("\t6.SEARCH A RECORD\n");
        printf("\t7.EXIT FROM ADDRESS BOOK\n");
        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice)
        {
        case 1:
        {
            printf("Enter number of records you want to enter: ");
            int n;
            scanf("%d", &n);
            clearInputBuffer();

            for (int i = 0; i < n; i++)
            {
                createRecord(fp);
            }
            break;
        }
        case 2:
            viewRecords(fp);
            break;
        // Implement other cases similarly
        default:
            printf("PLEASE ENTER THE CORRECT CHOICE\n");
            break;
        }
    }

    fclose(fp);
    return 0;
}
