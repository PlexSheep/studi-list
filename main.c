#include <stdio.h>

struct date {
    short date;
    short month;
    int year;
};

// Erstelle eine Studenten Struktur mit folgenden Inhalten: Nachname, Matrikelnummer, Start Datum, 
// End Datum, geburstdatum
struct student{
    int age;
    struct date birthday;
    char name[40];
    int matriculationNumber;
    struct date startdate;
    struct date enddate;
};

// make a global var to store all of our students. This is a pointer because we want to use malloc()
struct student* studentArr;
int studentArrLength = 0;

typedef struct node {
    struct student student;
    struct node* next;
}node;

struct student inputStudent(){

    struct student s;

    return s;
}

void addStudent(struct student* s){
    // TODO check if given student is already in the arr
   studentArr[studentArrLength++ + 1] = *s;
   int a = s->age;
}

// Schreibe eine Funktion in der die Anzahl der gespeicherten Studenten zurueck gegeben werden soll.
int getStudentenArrLength(){
    return studentArrLength;
}

// Schreibe eine funktion deleteStudent(matrikelnummer), welche einen Studenten loescht.
int deleteStudent(int mNum){
    for(int i = 0; i < getStudentenArrLength(); i++){
        if(mNum == studentArr[i].matriculationNumber)
            // delete that one

    }
    // return 0 on success, 1 on fail
    return 0;
}

int main(){
    return 0;
}
