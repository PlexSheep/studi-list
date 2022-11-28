#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct date {
    short day;
    short month;
    int year;
};

struct student{
    int* next;
    int age;
    struct date birthday;
    char name[50];
    char surname[50];
    int matriculationNumber;
    struct date startdate;
    struct date enddate;
};

// make a global var to store all of our students. This is a pointer because we want to use malloc()
struct student* studentArr;

struct student inputStudent(){
    char tmpnum[50];
    struct student s;

    printf("Geben sie ihr Alter ein:\n");
    fgets(tmpnum, 50, stdin);
    s.age = atoi(tmpnum);

    printf("Geben sie ihre Matrikelnummer ein\n");
    fgets(tmpnum, 50, stdin);
    s.matriculationNumber = atoi(tmpnum);
    
    printf("Geben sie ihr Geburtsdatum ein:\n");
    fgets(tmpnum, 50, stdin);
    int date[3];
    date[0] = atoi(strtok(tmpnum, "."));
    for(int i = 1; i < 3; i++){
        if(tmpnum[i] == ' '){
            break;
        }
        date[i] = atoi(strtok(NULL, "."));
    }   
    s.birthday.day = date[0];
    s.birthday.month = date[1];
    s.birthday.year = date[2];;

    printf("Geben sie ihren Vornamen ein:\n");
    fgets(s.name, 50, stdin);

    printf("Geben sie ihren Nachnamen ein:\n");
    fgets(s.surname, 50, stdin);
    
    printf("Geben sie ihr vorraussichtliches Startdatum ein\n");
    fgets(tmpnum, 50, stdin);
    
    date[0] = atoi(strtok(tmpnum, "."));
    for(int i = 1; i < 3; i++){
        if(tmpnum[i] == ' '){
            break;
        }
        date[i] = atoi(strtok(NULL, "."));
    }   
    s.startdate.day = date[0];
    s.startdate.month = date[1];
    s.startdate.year = date[2];;

    printf("Geben sie ihr vorraussichtliches Abschlussdatum ein\n");
    fgets(tmpnum, 50, stdin);
    
    date[0] = atoi(strtok(tmpnum, "."));
    for(int i = 1; i < 3; i++){
        if(tmpnum[i] == ' '){
            break;
        }
        date[i] = atoi(strtok(NULL, "."));
    }   
    s.enddate.day = date[0];
    s.enddate.month = date[1];
    s.enddate.year = date[2];;

    return s;
}

int main(){
    return 0;
}
