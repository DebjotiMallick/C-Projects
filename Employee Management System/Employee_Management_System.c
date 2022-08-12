#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

int main(){
    FILE *fp, *ft;
    char another, choice;
    
    struct emp{
        char name[30];
        int age;
        float salary;
    };

    struct emp e;
    char empname[30];
    long int resize;

    fp = fopen("Emp.dat", "rb+");
    if(fp == NULL){
        fp = fopen("Emp.dat", "wb+");
        if(fp == NULL){
            printf("Cannot open file");
            exit(1);
        }
    }

    resize = sizeof(e);
    while(1){
        system("cls");
        printf("1. Enter record\n\n");
        printf("2. List records\n\n");
        printf("3. Modify record\n\n");
        printf("4. Delete records\n\n");
        printf("5. Exit\n\n");
        printf("Your choice : ");
        fflush(stdin);
        choice = getche();
        switch(choice){
            case '1':
                system("cls");
                fseek(fp, 0, SEEK_END);
                another = 'y';
                while(another == 'y'){
                    printf("\nEnter name : ");
                    scanf("%s", e.name);
                    printf("\nEnter age : ");
                    scanf("%d", &e.age);
                    printf("\nEnter salary : ");
                    scanf("%f", &e.salary);
                    fwrite(&e, resize, 1, fp);
                    printf("Add another record ? (y/n) : ");
                    fflush(stdin);
                    another = getche();
                } 
                break;
            case '2':
                system("cls");
                rewind(fp);
                while(fread(&e, resize, 1, fp) == 1){
                    printf("%s %d %.02f\n", e.name, e.age, e.salary);
                }
                getch();
                break;
            case '3':
                system("cls");
                another = 'y';
                while(another == 'y'){
                    printf("Enter the employee name to modify : ");
                    scanf("%s", empname);
                    rewind(fp);
                    while(fread(&e, resize, 1, fp) == 1){
                        if(strcmp(e.name, empname) == 0){
                            printf("Enter new name, age and salary : ");
                            scanf("%s %d %f", e.name, &e.age, &e.salary);
                            fseek(fp, -resize, SEEK_CUR);
                            fwrite(&e, resize, 1, fp);
                            break;
                        }
                    printf("Modify another record ? (y/n) : ");
                    fflush(stdin);
                    another = getche();
                    }
                break;
                }
            case '4':
                system("cls");
                another = 'y';
                while(another == 'y'){
                    printf("Enter name of employee to delete : ");
                    scanf("%s", empname);
                    ft = fopen("Temp.dat", "wb");
                    rewind(fp);
                    while(fread(&e, resize, 1, fp) == 1){
                        if(strcmp(e.name, empname) != 0){
                            fwrite(&e, resize, 1, ft);
                        }
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("Emp.dat");
                    rename("Temp.dat", "Emp.dat");
                    fp = fopen("Emp.dat", "rb+");
                    printf("Delete another record ? (y/n) : ");
                    fflush(stdin);
                    another = getche();
                }
                break;
            case '5':
                fclose(fp);
                exit(0);

        }
    }
    return 0;

}