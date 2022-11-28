#include <stdio.h>
#include <stdlib.h>



int main(){
    struct Studenteninfo{
    int alter;
    int Geburtsdatum;
    char name[20];
    int matrikelnummer;
    int startdatum;
    int enddatum;
    };

    struct Studenteninfo *start = NULL;
    start=malloc(sizeof(struct Studenteninfo));
    if(start == NULL)
        return -1;
    int x,y,z,a,b;
    char* namenew;
    printf("Geben sie ihr Alter ein:\n");
    scanf("%d",&x);
    printf("Geben sie ihre Matrikelnummer ein\n");
    scanf("%d",&z);
    printf("Geben sie ihr Geburtsdatum ein(ohne Punkte):\n");
    scanf("%d",&y);
    printf("Geben sie ihren Nachnamen ein:\n");
    scanf("%s",&start->name,20);
    printf("Geben sie ihr Startdatum ein(ohne Punkte)\n");
    scanf("%d",&a);
    printf("Geben sie ihr vorraussichtliches Abschlussdatum ein(ohne Punkte)\n");
    scanf("%d",&b);
    
    start->alter=x;
    start->Geburtsdatum=y;
    start->matrikelnummer=z;
    start->startdatum=a;
    start->enddatum=b;

    printf("alter:\t\t%d\ngeburtstag:\t%d\nmatrikelnummer:\t%d\nName:\t%s\nstartdatum:\t%d\nenddatum:\t%d\n", start->alter, start->Geburtsdatum, start->matrikelnummer, start->name, start->startdatum,start->enddatum);
    
    return 0;
}

   