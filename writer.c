#include <stdio.h>
#include <string.h>

int main()
{
    
    int age, matriculationnumber;
    char birthday[50];
    char name[50];
    char surname[50];
    
    char startdate[50];
    char enddate[50];

    FILE* fp = fopen("student.csv","a");
    
    //wenns beim öffnen n Error gibt
    if (!fp){
        printf("Cant open file\n");
        return 0;
    }
    //Eingaben einlesen und speichern
    printf("\nPls put all names in quotation marks\n");
    printf("\nEnter Age\n");
    scanf("%d",&age);
    printf("\nEnter d.o.b\n");
    scanf("%s", &birthday);
    printf("\nEnter Name\n");
    scanf("%s", &name);
    printf("\n Enter Surname\n");
    scanf("%s", &surname);
    printf("\nEnter matriculationnumber\n");
    scanf("%d",&matriculationnumber);
    printf("\nEnter startdate\n");
    scanf("%s",&startdate);
    printf("\nEnter enddate\n");
    scanf("%s",&enddate);

    //speichern
    fprintf(fp,"%d,%s,%s,%s,%d,%s,%s\n", age, birthday, name, surname, matriculationnumber, startdate, enddate );

    printf("\n Added! \n");

    fclose(fp);
    return(0);
}
