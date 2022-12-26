#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "./interface.h"

struct date {
    short day;
    short month;
    int year;
};

// Erstelle eine Studenten Struktur mit folgenden Inhalten: Nachname, Matrikelnummer, Start Datum, 
// End Datum, geburstdatum
typedef struct student {
    int age;
    struct date birthday;
    char name[50];
    char surname[50];
    int matriculationNumber;
    struct date startdate;
    struct date enddate;
    struct student* next;
    struct student* last;
}student;

// make a global var to store all of our students. This is a pointer because we want to use malloc()
int studentListLength = 0;

student* head = NULL;  // first node
student* tail = NULL;  // last node

struct date parseDate(char* cptr){
    // TODO check if the given string is a proper date, maybe using scanf?
    // return NULL if bad
    struct date d;
    struct date* dptr = &d;
    char* part[3];   // TODO check if this is enough if names are fully filled.

    // TODO FIXME SEGFAULT WITH WRONG INPUT!
    part[0] = strtok(cptr, ".");    // day
    part[1] = strtok(NULL, ".");    // month
    part[2] = strtok(NULL, ".");    // year

    // debug printf, remove later or comment
    if(part[0]!=NULL&&part[1]!=NULL&&part[2]!=NULL){
        dptr->day = atoi(part[0]);
        dptr->month = atoi(part[1]);
        dptr->year = atoi(part[2]);
    }
    else{
        dptr->day=-1;
        dptr->month=-1;
        dptr->year=-1;
    }

    return d;
}

void removeQuotes(char* cptr){
    int j = 0;
    for (int i = 0; i < strlen(cptr); i ++) {
        if (cptr[i] != '"' && cptr[i] != '\\') { 
            cptr[j++] = cptr[i];
        } else if (cptr[i+1] == '"' && cptr[i] == '\\') { 
            cptr[j++] = '"';
        } else if (cptr[i+1] != '"' && cptr[i] == '\\') { 
            cptr[j++] = '\\';
        }
    }

    //You missed the string termination ;)
    if(j>0) cptr[j]=0;
}

student* inputStudent(){
    /*
########################################################################
# input method for the students                                        #
# reads strings from stdin and retruns a student struct                #
########################################################################
*/

    // tmpnum array to use fgets as as safe input function. Later converted to number formats
    char tmpnum[50];

    // Create student struct and allocate memory
    student *s = (student*) malloc(sizeof(student));

    if(s == NULL){
        printf("Could not allocate Memory for new student.");
        exit(EXIT_FAILURE);
    }

    // TODO add validations for user input.
    printf("Geben sie ihr Alter ein:\n");
    fgets(tmpnum, 50, stdin);
    s -> age = atoi(tmpnum);

    printf("Geben sie ihre Matrikelnummer ein\n");
    fgets(tmpnum, 50, stdin);
    s -> matriculationNumber = atoi(tmpnum);

    printf("Geben sie ihr Geburtsdatum ein:\n");
    fgets(tmpnum, 50, stdin);
    // TODO check for invalid date (-1.-1.-1)
    s->birthday = parseDate(tmpnum);

    printf("Geben sie ihren Vornamen ein:\n");
    fgets(s -> name, 50, stdin);
    // FIXME \n is stored here aswell, which fucks everything up
    s->name[strcspn(s->name, "\n")] = 0;

    printf("Geben sie ihren Nachnamen ein:\n");
    fgets(s -> surname, 50, stdin);
    // FIXME \n is stored here aswell, which fucks everything up
    s->surname[strcspn(s->surname, "\n")] = 0;

    printf("Geben sie ihr vorraussichtliches Startdatum ein\n");
    fgets(tmpnum, 50, stdin);
    // TODO check for invalid date (-1.-1.-1)
    s->startdate = parseDate(tmpnum);

    printf("Geben sie ihr vorraussichtliches Abschlussdatum ein\n");
    fgets(tmpnum, 50, stdin);
    // TODO check for invalid date (-1.-1.-1)
    s->enddate = parseDate(tmpnum);

    return s;
}

// Schreibe eine Funktion in der die Anzahl der gespeicherten Studenten zurueck gegeben werden soll.
int getStudentenListLength(){
    return studentListLength;
}

int addStudent(student* s){ 
    /*
########################################################################
# Method to add a student to the linked list                           #
########################################################################
*/

    if(studentListLength == 0){
        // no elements in list yet, create the first.
        head = s;
        head -> last = NULL;
        head -> next = NULL;
        tail = s;
        tail -> next = NULL;
        studentListLength++;
        return 0;
    }
    else {
        student *inode = head;
        if(s -> surname[0] < head -> surname[0]){
            s -> next = head;
            head = s;
            studentListLength++;
            return 0;
        }
        // FIXME is this a good idea? might cause trouble when looping to find stuff
        // This seems like hacky and bad code.

        while (inode -> next != NULL && s -> surname[0] > inode -> next -> surname[0]) {
            //printf("%c", s -> surname[0]);
            inode = inode -> next;
        } 

        s -> next = inode -> next;
        inode -> next = s;

        if(inode == tail){
            tail = s;
        }

        studentListLength++;
        return 0;
    }
}

// Bogus Code
/*
// FIXME is this a good idea? might cause trouble when looping to find stuff
// This seems like hacky and bad code.
student *inode = head;
while (inode -> next != NULL) {
printf("%c", s -> surname[0]);
if(s -> surname[0] > inode -> next -> surname[0] && s -> surname[0] < inode -> next -> next -> surname[0]){
student *tmpStud = inode -> next -> next; 
inode -> next = s;
s -> next = tmpStud;
return 0;
}
inode = inode -> next;
} 

// Case if stidentListLenght is equal to 1
head -> next = s;
s -> next = NULL;
tail = s;
studentListLength++;  
return 0;
}
*/

// Schreibe eine funktion deleteStudent(matrikelnummer), welche einen Studenten loescht.
// TODO rewrite with nodes
int deleteStudent(int mNum){
    /*
########################################################################
# Method to delete students in by matriculation number                 #
########################################################################
*/
    student *inode = head;

    // If this case is true, it is either the last or only element in the list and the method should terminate once it is freed
    if(inode -> matriculationNumber == mNum){
        student *oldHead = head;
        head = head -> next;
        free(oldHead);
        studentListLength--;
        return 0;
    }

    // If above condition is not met, below code walks through the list and checks for the matchning matriculation number.
    // If match is found, code frees and NULL's the matche
    int foundCounter = 0;
    while(inode -> next -> matriculationNumber != mNum && inode != NULL){
        inode = inode -> next;
        foundCounter++;
        if(foundCounter >= studentListLength){
            printf("Student nicht gefunden");
            return 1;
        }
    }
    student *oldNext = inode -> next;
    inode -> next = inode -> next -> next;
    free(oldNext);
    oldNext = NULL;
    studentListLength--;
    printf("");
    return 0;

}

int recursiveDestroy(student *del){
    /*
########################################################################
# Method to free the memory allocated in heap for the students         # 
# on programm exit                                                     #
########################################################################
*/
    // Only execute if head was not already deleted or empty to begin with to avoid use after free
    if(del != NULL){
        if(del == tail){
            //printf("Deleted until head\n"); //DEBUG:
            free(del);
            del = NULL;
            //free(del);
        }
        else {
            recursiveDestroy(del -> next);
            //free(del -> student);
            free(del);
            del = NULL;
        }
    }
    return 0;
}

void printAllStudents(){
    /*
########################################################################
# Method to print all students                                         # 
########################################################################
*/
    student *inode = head;
    if(studentListLength > 0 && inode != NULL){
        student *s = head;
        if(studentListLength > 0 && s != NULL){
            for (int i = 0; i < studentListLength; i++){
                printf("Name: %s\n", s -> name);
                printf("Surname: %s\n", s -> surname);
                printf("Age: %d\n", s -> age);
                printf("Mnumber: %d\n", s -> matriculationNumber);
                printf("Bithdate: %d.%d.%d\n", s -> birthday.day, s -> birthday.month, s -> birthday.year);
                printf("Startdate: %d.%d.%d\n", s -> startdate.day, s -> startdate.month, s -> startdate.year);
                printf("Enddate: %d.%d.%d\n", s -> enddate.day, s -> enddate.month, s -> enddate.year);
                printf("------------------------------------\n");
                if(s->next != NULL)
                    s = s -> next;
            }
        }
        /*
           else if (studentListLength == 1) {
           printf("%d", head -> student -> age);
           }
           */
    }
}

off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n", filename,
            strerror(errno));

    return -1;
}


int readCSV(){
    if(fsize("student.csv")>0){
        FILE* stream = fopen("student.csv", "r");
        if(stream==NULL){
            printf("Could not open student.csv!\n");
            return 2;
        }
        char* line = malloc(sizeof(char)*1024);
        if(line==NULL){
            printf("Could not get memory!\n");
            return 1;
        }
        char* part[7];   // TODO check if this is enough if names are fully filled.
        student* s;
        while (fgets(line, 1024, stream)){
            s = malloc(sizeof(student));
            if(s==NULL){
                printf("Could not get memory!\n");
                return 1;
            }
            part[0] = strtok(line, ",");    // age
            part[1] = strtok(NULL, ",");    // birthday
            part[2] = strtok(NULL, ",");    // name
            part[3] = strtok(NULL, ",");    // surname
            part[4] = strtok(NULL, ",");    // matriculationNumber
            part[5] = strtok(NULL, ",");    // startdate
            part[6] = strtok(NULL, ",");    // enddate

            // Debug: print all parts
            // printf("%s|%s|%s|%s|%s|%s|%s", part[0], part[1], part[2], part[3], part[4], part[5], part[6]);

            s->age = atoi(part[0]);
            // TODO check for invalid date (-1.-1.-1)
            s->birthday = parseDate(part[1]);
            removeQuotes(part[2]);
            strcpy(s->name, part[2]);
            removeQuotes(part[3]);
            strcpy(s->surname, part[3]);
            s->matriculationNumber = atoi(part[4]);
            // TODO check for invalid date (-1.-1.-1)
            s->startdate = parseDate(part[5]);
            // TODO check for invalid date (-1.-1.-1)
            s->enddate = parseDate(part[6]);

            // printf("Name: %s\n", s -> name);
            // printf("Surname: %s\n", s -> surname);
            // printf("Age: %d\n", s -> age);
            // printf("Mnumber: %d\n", s -> matriculationNumber);
            // printf("Bithdate: %d.%d.%d\n", s -> birthday.day, s -> birthday.month, s -> birthday.year);
            // printf("Startdate: %d.%d.%d\n", s -> startdate.day, s -> startdate.month, s -> startdate.year);
            // printf("Enddate: %d.%d.%d\n\n", s -> enddate.day, s -> enddate.month, s -> enddate.year);
            // FIXME adding the done students doesn't work
            addStudent(s);
        }
        fclose(stream);
        free(line);
        // don't free s here, we will need it for as long as the process runs!
    }
    return 0;
}

void printStudent(int Martik){
    student *s = head;
    int fund=0;
    if(studentListLength > 0 && s != NULL){
        for(int i=0;i<studentListLength;i++){
            if(Martik == s ->matriculationNumber){
                printf("Name: %s\n", s -> name);
                printf("Surname: %s\n", s -> surname);
                printf("Age: %d\n", s -> age);
                printf("Mnumber: %d\n", s -> matriculationNumber);
                printf("Bithdate: %d.%d.%d\n", s -> birthday.day, s -> birthday.month, s -> birthday.year);
                printf("Startdate: %d.%d.%d\n", s -> startdate.day, s -> startdate.month, s -> startdate.year);
                printf("Enddate: %d.%d.%d\n\n", s -> enddate.day, s -> enddate.month, s -> enddate.year);
                fund=1;
                break;
            }
            s = s-> next;
        }
        if(fund==0){
            printf("Unter dieser Martikulartionsnummer ist kein Student gespeichert.");
        }
    }
}

void debugTests(){
    // Test for removeQuotes(char*)
    const char cptrE[] = "TESTSTRINGTESTSTRINGTESTTESTSTRINGSTRING";
    printf("[DEBUG]Testing removeQuotes(char* cptr), output should be [%s].\n", cptrE);
    char cptr[] = "\"TESTSTRING\"\"TESTSTRING\"\"TEST\"TESTSTRING\"STRING\"";
    removeQuotes(cptr);
    printf("[%s]\n", cptr);
    if(!strcmp(cptrE, cptr)) printf("SUCCESS!\n");
    else printf("FAILURE!\n");

    // Your code goes here
}

int saveCSV(){
    if(studentListLength){
        student* s = head;
        FILE* fp = fopen("student.csv", "w");
        if(fp==NULL){
            return 1;
        }
        for(int i=0;i<studentListLength;i++){
            fprintf(fp,"%d,%d.%d.%d,\"%s\",\"%s\",%d,%d.%d.%d,%d.%d.%d\n", s->age, s->birthday.day, s->birthday.month, s->birthday.year, s->name, s->surname, s->matriculationNumber, s->startdate.day, s->startdate.month, s->startdate.year, s->enddate.day, s->enddate.month, s->enddate.year);
            if(s!=tail)
                s = s->next;
        }
        fclose(fp);
    }
    return 0;
}

int main(){
    /*
########################################################################
# The main method takes care of the menu and menu                      #
# user input functionality                                             #
########################################################################
*/
    drawInterface();
    getc(stdin);
    int wahl;
    char tmpnum[50];
    int ret = 0;

    if(readCSV()){
        // reading the file failed.
        printf("Fatal error while reading from students.csv, exiting...\n");
        exit(EXIT_FAILURE);
    }

    do{
        printf("\e[1;1H\e[2J"); // This is the ANSI escape sequence to clear the terminal and set coursor to start position. Used for fancy TUI
        printf("Bitte Wahl treffen:\n");
        printf("(1) Neuen Studenten anlegen\n");
        printf("(2) Anzahl der gespeicherten Studenten abrufen\n");
        printf("(3) Student anhand der Martikelnummer ausgeben\n");
        printf("(4) Alle Studenten alphabetisch ausgeben\n");
        printf("(5) Studenten loeschen\n");
        printf("(6) Programm beenden\n");
        printf("(7) Debug Testing\n");
        fgets(tmpnum, 50, stdin);
        wahl = atoi(tmpnum);

        switch(wahl){
            case 1:
                printf("\e[1;1H\e[2J");
                addStudent(inputStudent());
                break;
            case 2:
                printf("\e[1;1H\e[2J");
                printf("Aktuelle Studenten Anzahl: %d\n", getStudentenListLength());
                break;
            case 3:
                printf("\e[1;1H\e[2J");
                printf("Matrikulationsnummer eingeben:\n");
                fgets(tmpnum, 50, stdin);
                printStudent(atoi(tmpnum));
                break;
            case 4:
                printf("\e[1;1H\e[2J");
                printAllStudents();
                break;
            case 5:
                printf("\e[1;1H\e[2J");
                printf("Matrikulationsnummer eingeben: ");
                fgets(tmpnum, 50, stdin);
                if(tmpnum[0] != ' '){deleteStudent(atoi(tmpnum));}
                else {printf("Falsche Eingabe");}      
                break;
            case 6:
                ret = saveCSV();
                if(ret){
                    printf("\e[1;1H\e[2J");
                    printf("NICHT ALLE STUDENTEN KONNTEN IN DIE DATEI GESPEICHERT WERDEN!\nDAS PROGRAMM ENDET NICHT!\nGEBEN SIE 'F' EIN UM BEENDEN ZU ERZWINGEN: ");
                    char c = getc(stdin);
                    if(c != 'F')
                        break;
                }
                recursiveDestroy(head);
                return ret;
            case 7:
                printf("\e[1;1H\e[2J");
                debugTests();
                break;
            default:
                printf("Bitte einen gueltigen Wert eingeben\n");
                break;
        }
        // FIXME it would be good practice to use the same input function for all inputs
        getc(stdin);
    }while(1);
}
