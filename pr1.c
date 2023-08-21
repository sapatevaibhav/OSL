#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

struct Employee {
    int id;
    char name[50];
    char mobile[15];
    float salary;
};

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char fname[50];
    printf("ENTER ADDRESS BOOK NAME: ");
    scanf("%s", fname);
    FILE *fp = fopen(fname, "w");
    fprintf(fp, "ID \t\t NAME\t\t MOB_NO\t\t SALARY\n");
    fclose(fp);

    int choice;
    while (1) {
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

        switch (choice) {
            case 1: {
                printf("Enter number of records you want to enter: ");
                int n;
                scanf("%d", &n);
                clearInputBuffer();
                
                FILE *fp = fopen(fname, "a");
                for (int i = 0; i < n; i++) {
                    struct Employee emp;
                    printf("ENTER ID OF EMPLOYEE: ");
                    scanf("%d", &emp.id);
                    printf("ENTER NAME OF EMPLOYEE: ");
                    clearInputBuffer();
                    fgets(emp.name, sizeof(emp.name), stdin);
                    emp.name[strlen(emp.name) - 1] = '\0'; // Remove newline character
                    printf("ENTER MOBILE NO. OF EMPLOYEE: ");
                    scanf("%s", emp.mobile);
                    printf("ENTER SALARY OF EMPLOYEE: ");
                    scanf("%f", &emp.salary);
                    fprintf(fp, " %d \t\t%s \t\t %s \t %.2f\n", emp.id, emp.name, emp.mobile, emp.salary);
                }
                fclose(fp);
                break;
            }
            case 2: {
                FILE *fp = fopen(fname, "r");
                char c;
                while ((c = fgetc(fp)) != EOF) {
                    printf("%c", c);
                }
                fclose(fp);
                break;
            }
            case 3: {
                struct Employee emp;
                FILE *fp = fopen(fname, "a");
                printf("ENTER ID OF EMPLOYEE: ");
                scanf("%d", &emp.id);
                printf("ENTER NAME OF EMPLOYEE: ");
                clearInputBuffer();
                fgets(emp.name, sizeof(emp.name), stdin);
                emp.name[strlen(emp.name) - 1] = '\0'; // Remove newline character
                printf("ENTER MOBILE NO. OF EMPLOYEE: ");
                scanf("%s", emp.mobile);
                printf("ENTER SALARY OF EMPLOYEE: ");
                scanf("%f", &emp.salary);
                fprintf(fp, " %d \t\t%s \t\t %s \t %.2f\n", emp.id, emp.name, emp.mobile, emp.salary);
                fclose(fp);
                break;
            }
            case 4: {
                int eidToDelete;
                printf("ENTER EMPLOYEE ID TO BE DELETED: ");
                scanf("%d", &eidToDelete);
                FILE *inFile = fopen(fname, "r");
                FILE *outFile = fopen("temp.txt", "w");
                char line[200];
                int found = 0;
                while (fgets(line, sizeof(line), inFile)) {
                    int id;
                    sscanf(line, "%d", &id);
                    if (id != eidToDelete) {
                        fputs(line, outFile);
                    } else {
                        found = 1;
                    }
                }
                fclose(inFile);
                fclose(outFile);
                if (found) {
                    remove(fname);
                    rename("temp.txt", fname);
                    printf("RECORD DELETED\n");
                } else {
                    remove("temp.txt");
                    printf("ERROR: RECORD DOES NOT EXIST!!\n");
                }
                break;
            }
            case 5: {
                int eidToModify;
                printf("ENTER EMPLOYEE ID TO BE MODIFIED: ");
                scanf("%d", &eidToModify);
                FILE *inFile = fopen(fname, "r");
                FILE *outFile = fopen("temp.txt", "w");
                char line[200];
                int found = 0;
                while (fgets(line, sizeof(line), inFile)) {
                    int id;
                    sscanf(line, "%d", &id);
                    if (id != eidToModify) {
                        fputs(line, outFile);
                    } else {
                        found = 1;
                    }
                }
                fclose(inFile);
                fclose(outFile);
                if (found) {
                    remove(fname);
                    rename("temp.txt", fname);

                    struct Employee emp;
                    FILE *fp = fopen(fname, "a");
                    emp.id = eidToModify;
                    printf("ENTER NAME OF EMPLOYEE: ");
                    clearInputBuffer();
                    fgets(emp.name, sizeof(emp.name), stdin);
                    emp.name[strlen(emp.name) - 1] = '\0'; // Remove newline character
                    printf("ENTER MOBILE NO. OF EMPLOYEE: ");
                    scanf("%s", emp.mobile);
                    printf("ENTER SALARY OF EMPLOYEE: ");
                    scanf("%f", &emp.salary);
                    fprintf(fp, " %d \t\t%s \t\t %s \t %.2f\n", emp.id, emp.name, emp.mobile, emp.salary);
                    fclose(fp);

                    printf("RECORD MODIFIED\n");
                } else {
                    remove("temp.txt");
                    printf("ERROR: RECORD DOES NOT EXIST!!\n");
                }
                break;
            }
            case 6: {
                int eidToSearch;
                printf("ENTER EMPLOYEE ID TO BE SEARCHED: ");
                scanf("%d", &eidToSearch);
                FILE *fp = fopen(fname, "r");
                char line[200];
                int found = 0;
                while (fgets(line, sizeof(line), fp)) {
                    int id;
                    sscanf(line, "%d", &id);
                    if (id == eidToSearch) {
                        printf("%s", line);
                        found = 1;
                        break;
                    }
                }
                fclose(fp);
                if (found) {
                    printf("RECORD FOUND...!!!\n");
                } else {
                    printf("ERROR: RECORD DOES NOT EXIST!!!\n");
                }
                break;
            }
            case 7: {
                printf("THANK YOU\n");
                exit(0);
            }
            default:
                printf("PLEASE ENTER THE CORRECT CHOICE\n");
                break;
        }
    }

    return 0;
}
