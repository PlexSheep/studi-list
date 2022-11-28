#include <stdio.h>

struct date {
    short date;
    short month;
    int year;
};

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

struct student inputStudent(){

    struct student s;

    return s;
}

void addStudent(struct student* s){
    // TODO check if given student is already in the arr
   studentArr[studentArrLength++ + 1] = *s;
}

int main(){
    return 0;
}
