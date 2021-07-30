#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>

char ans = 0;
int ok;
int b, valid = 0;

void WelcomeScreen();
void Title();
void MainMenu();
void LoginScreen();
void add_rec();
void search_rec();
void edit_rec();
void del_rec();
void list_rec();
void ex_it();
void gotoxy(short x, short y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

struct patient{
    int age;
    char gender[20];
    char FirstName[20];
    char LastName[20];
    char contact[15];
    char city[20];
    char doctor[20];
    char problem[30];
} p, temp;

void main(){
    WelcomeScreen();
    Title();
    LoginScreen();
}

void WelcomeScreen(){
    char ch;
    printf("\n\n\n\n\n\t\t\t\t   -------------------------------------------\n");
    printf("\t\t\t\t\t\t   Welcome to\n");
    printf("\t\t\t\t\tKolkata Hospital Management System\n");
    printf("\t\t\t\t   -------------------------------------------\n");
    printf("\n\t\t\t\t   Press ENTER key to continue...");
    do{
        fflush(stdin);
        ch = getch();
    } while(ch != 13);
    system("cls");
}

void Title(){
    printf("\n\t\t\t   -------------------------------------------\n");
    printf("\t\t\t        Kolkata Hospital Management System\n");
    printf("\t\t\t   -------------------------------------------\n");
}

void LoginScreen(){
    int i, e = 0;
    char Username[20];
    char Password[20];
    char OriginalUsername[20] = "Debjoti";
    char OriginalPassword[20] = "1234";
    do{
        printf("\n\t\t\t   Enter username and password\n");
        printf("\n\t\t\t   Username : ");
        scanf("%s", Username);
        printf("\n\t\t\t   Password : ");
        for(i = 0; i < 4; i++){
            Password[i] = getch();
            printf("*");
        }
        Password[i] = '\0';
        if(strcmp(Username, OriginalUsername)==0 && strcmp(Password, OriginalPassword)==0){
            gotoxy(27,11);
            printf("Logging in");
            gotoxy(37,11);
            printf(".");
            Sleep(1000);
            gotoxy(38,11);
            printf(".");
            Sleep(1000);
            gotoxy(39,11);
            printf(".");
            Sleep(500);
            MainMenu();
            break;
        } else {
            printf("\n\t\t\t   Password incorrect, try again? (y/n) : ");
            e++;
            getch();
        } 
    } while (e <= 2);
    if(e>2){
        printf("\nYou have crossed the limit. You cannot login.");
        ex_it();
    }
    system("cls");
}

void MainMenu(){
    system("cls");
    int choice;
    Title();
    printf("\n\t\t\t     1. Add patient record\n");
    printf("\n\t\t\t     2. List patient record\n");
    printf("\n\t\t\t     3. Search patient record\n");
    printf("\n\t\t\t     4. Edit patient record\n");
    printf("\n\t\t\t     5. Delete patient record\n");
    printf("\n\t\t\t     6. Exit\n");
    printf("\n\t\t\t     Enter your choice : ");
    scanf("%d", &choice);
    switch(choice){
        case 1: 
            add_rec();
            break;
        case 2:
            list_rec();
            break;
        case 3: 
            search_rec();
            break;
        case 4:
            edit_rec();
            break;
        case 5: 
            del_rec();
            break;
        case 6:
            ex_it();
            break;
        default: 
            system("cls");
            Title();
            printf("\n\n\n\n\n\n\t\t\t      --------Invalid entry. Please try again--------");
            Sleep(1500);
            MainMenu();
    }
}

void ex_it(){
    system("cls");
    Title();
    gotoxy(27,11);
    printf("Closing system, please wait");
    gotoxy(54,11);
    printf(".");
    Sleep(1000);
    gotoxy(55,11);
    printf(".");
    Sleep(1000);
    gotoxy(56,11);
    printf(".");
    Sleep(500);
}

void add_rec(){
    system("cls");
    Title();
    char ans;
    FILE *fp;
    fp = fopen("Record.txt", "a");
    printf("\n\t\t\t   -------------Add patients record-------------");
    A:
    printf("\n\n\t Enter first name : ");
    scanf("%s", p.FirstName);
    p.FirstName[0] = toupper(p.FirstName[0]);
    if(strlen(p.FirstName)>20 || strlen(p.FirstName) < 2){
        printf("\n\t Invalid name.......range is 2-20");
        goto A;
    } else {
        for (b = 0; b < strlen(p.FirstName); b++)
        {
            if(isalpha(p.FirstName[b])){
                valid = 1;
            } else {
                valid = 0;
                break;
            }
        }
        if(!valid){
            printf("\n\t Invalid name, Enter again.");
            goto A;
        }
        
    }

    B:
    printf("\n\t Enter last name : ");
    scanf("%s", p.LastName);
    p.LastName[0] = toupper(p.LastName[0]);
    if(strlen(p.LastName)>20 || strlen(p.LastName) < 2){
        printf("\n\t Invalid name.......range is 2-20");
        goto B;
    } else {
        for (b = 0; b < strlen(p.LastName); b++)
        {
            if(isalpha(p.LastName[b])){
                valid = 1;
            } else {
                valid = 0;
                break;
            }
        }
        if(!valid){
            printf("\n\t Invalid name, Enter again.");
            goto B;
        }
        
    }

    do{
        printf("\n\t Enter gender : ");
        scanf("%s", p.gender);   
    } while(p.gender == "");
    p.gender[0] = toupper(p.gender[0]);

    do{
        printf("\n\t Enter age : ");
        scanf("%i", &p.age);
    } while(p.age<=0);
 
   
    printf("\n\t Enter city : ");
    scanf("%s", p.city);
    p.city[0] = toupper(p.city[0]);

    printf("\n\t Enter contact number : ");
    scanf("%s", p.contact);

    do{
        printf("\n\t Enter problem : ");
        scanf("%s", p.problem);
    } while(p.problem == "");
    p.problem[0] = toupper(p.problem[0]);

    do{
        printf("\n\t Prescribed doctor : ");
        scanf("%s", p.doctor);
    } while(p.doctor == "");
    p.doctor[0] = toupper(p.doctor[0]);

    fprintf(fp, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);
    printf("\n\t Information record successful.");
    fclose(fp);
    Sleep(1000);
    printf("\n\t Do you want to add more ? (y/n) : ");
    sd:
    scanf("%c", &ans);
    if(toupper(ans) == 'Y'){
        add_rec();
    } else if(toupper(ans) == 'N'){
        printf("\t Thank you!\n");
        Sleep(1500);
        MainMenu();
    } else {
        //printf("\nInvalid input.");
        goto sd;
    }
}

void list_rec(){
    int row;
    system("cls");
    Title();
    FILE *fp;
    fp = fopen("Record.txt", "r");
    printf("\n\t\t\t   -----------List of patients records--------------");
    gotoxy(1, 8);
    printf("Full Name");    
    gotoxy(22, 8);
    printf("Gender"); 
    gotoxy(30, 8);
    printf("Age"); 
    gotoxy(37, 8);
    printf("city"); 
    gotoxy(51, 8);
    printf("Contact"); 
    gotoxy(65, 8);
    printf("Problem"); 
    gotoxy(75, 8);
    printf("Prescribed doctor"); 
    printf("\n---------------------------------------------------------------------------------------------------------");
    row = 10;
    while(fscanf(fp, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, &p.age, p.city, p.contact,p.problem, p.doctor) != EOF){
        gotoxy(1, row);
        printf("%s %s", p.FirstName, p.LastName);    
        gotoxy(22, row);
        printf("%s", p.gender); 
        gotoxy(30, row);
        printf("%i", p.age); 
        gotoxy(37, row);
        printf("%s", p.city); 
        gotoxy(51, row);
        printf("%s", p.contact); 
        gotoxy(65, row);
        printf("%s", p.problem); 
        gotoxy(75, row);
        printf("%s", p.doctor); 
        row++;
    }
    fclose(fp);
    getch();
    MainMenu();

}

void search_rec(){
    int flag = 0;
    char name[20];
    system("cls");
    Title();
    FILE *fp;
    fp = fopen("Record.txt", "r");
    printf("\n\t\t\t   --------------Search patients record---------------");
    gotoxy(12, 8);
    printf("\n\t Enter patients name to be viewed : ");
    scanf("%s", name);
    fflush(stdin);
    name[0] = toupper(name[0]);
    while(fscanf(fp, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, &p.age, p.city, p.contact, p.problem, p.doctor) != EOF){
        if(strcmp(p.FirstName, name) == 0){
            flag = 1;
            gotoxy(1, 8);
            printf("Full Name");    
            gotoxy(20, 8);
            printf("Gender"); 
            gotoxy(32, 8);
            printf("Age"); 
            gotoxy(37, 8);
            printf("city"); 
            gotoxy(49, 8);
            printf("Contact"); 
            gotoxy(65, 8);
            printf("Problem"); 
            gotoxy(75, 8);
            printf("Prescribed doctor"); 
            printf("\n---------------------------------------------------------------------------------------------------------");
            gotoxy(1, 10);
            printf("%s %s", p.FirstName, p.LastName);    
            gotoxy(20, 10);
            printf("%s", p.gender); 
            gotoxy(32, 10);
            printf("%i", p.age); 
            gotoxy(37, 10);
            printf("%s", p.city); 
            gotoxy(49, 10);
            printf("%s", p.contact); 
            gotoxy(65, 10);
            printf("%s", p.problem); 
            gotoxy(75, 10);
            printf("%s", p.doctor); 
            } 
        }
        if(flag == 0){
            gotoxy(5, 10);
            printf("\n\t Record not found\n");
            Sleep(1500);
        }
        fclose(fp);
        L:
        printf("\n\n\t Do you want to view more? (y/n) : ");
        scanf("%c", &ans);
        if(toupper(ans) == 'Y'){
            search_rec();
        } else if(toupper(ans) == 'N'){
            printf("\n\t Thank you.\n");
            Sleep(1500);
            MainMenu();
        } else {
            printf("\n\t Invalid input.");
            goto L;
        }
    }


void edit_rec(){
    FILE *fp, *ft;
    int i , b , valid = 0;
    char ch;
    char name[20];
    system("cls");
    Title();
    ft = fopen("Temp.txt", "w+");
    fp = fopen("Record.txt", "r");
    if(fp == NULL){
        printf("\n\t Cannot open file\n");
        getch();
        MainMenu();
    }
    printf("\n\t\t\t   -----------Edit patients record------------");
    gotoxy(12, 8);
    printf("Enter the first name of the patient : ");
    scanf("%s", name);
    fflush(stdin);
    name[0] = toupper(name[0]);
    gotoxy(12, 10);
    if(ft == NULL){
        printf("\n\t Cannot open file\n");
        getch();
        MainMenu();
    }
    while(fscanf(fp, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, &p.age, p.city, p.contact, p.problem, p.doctor) != EOF){
        if(strcmp(p.FirstName, name) == 0){
            valid = 1;
            gotoxy(12, 10);
            printf("Existing record");
            gotoxy(12, 12);
            printf("----------------");
            gotoxy(12, 14);
            printf("%s \t%s \t%s \t%i \t%s \t%s \t%s \t%s", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);
            gotoxy(12, 16);
            printf("First Name : ");    
            scanf("%s", p.FirstName);
            gotoxy(12, 18);
            printf("Last Name : ");    
            scanf("%s", p.LastName);
            gotoxy(12, 20);
            printf("Gender : "); 
            scanf("%s", p.gender);
            p.gender[0] = toupper(p.gender[0]);
            gotoxy(12, 22);
            printf("Age : "); 
            scanf("%i", &p.age);
            gotoxy(12, 24);
            printf("City : "); 
            scanf("%s", p.city);
            p.city[0] = toupper(p.city[0]);
            gotoxy(12, 26);
            printf("Contact : "); 
            scanf("%s", p.contact);
            gotoxy(12, 28);
            printf("Problem : "); 
            scanf("%s", p.problem);
            p.problem[0] = toupper(p.problem[0]);
            gotoxy(12, 30);
            printf("Prescribed doctor : "); 
            scanf("%s", p.doctor);
            p.doctor[0] = toupper(p.doctor[0]);
            gotoxy(12, 32);
            printf("\n\t Enter 'U' character for the updation operation");
            ch = getche();
            if(ch == 'u' || ch == 'U'){
                fprintf(ft, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);
                gotoxy(12, 34);
                printf("Patient record updated successfully");
            }
        } else {
            fprintf(ft, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);

        }
    }
    if(!valid){
        gotoxy(12, 10);
        printf("No record found");
    }
    fclose(fp);
    fclose(ft);
    remove("Record.txt");
    rename("Temp.txt", "Record.txt");
    getch();
    MainMenu();

}


void del_rec(){
    FILE *fp, *ft;
    int i , b , found = 0;
    char ch;
    char name[20];
    system("cls");
    Title();
    ft = fopen("Temp_file.txt", "w+");
    fp = fopen("Record.txt", "r");
    printf("\n\t\t\t   -----------Delete patients record------------");
    gotoxy(12, 8);
    printf("\n\t Enter the first name of the patient : ");
    scanf("%s", name);
    fflush(stdin);
    name[0] = toupper(name[0]);
    gotoxy(12, 10);
    while(fscanf(fp, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, &p.age, p.city, p.contact, p.problem, p.doctor) != EOF){
        if(strcmp(p.FirstName, name) != 0){    
            fprintf(ft, "%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);
        } else {
            gotoxy(12, 10);
            printf("%s %s %s %i %s %s %s %s\n", p.FirstName, p.LastName, p.gender, p.age, p.city, p.contact, p.problem, p.doctor);
            found = 1;
        }
    }
    if(found == 0){
        printf("\n\t No record found");
        getch();
        MainMenu();
    } else {
        fclose(fp);
        fclose(ft);
        remove("Record.txt");
        rename("Temp.txt", "Record.txt");
        gotoxy(12, 12);
        printf("Record deleted successfully.");
        getch();
        MainMenu();
    }
}