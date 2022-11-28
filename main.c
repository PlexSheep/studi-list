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


int main(){
    return 0;
}
