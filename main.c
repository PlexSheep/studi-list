#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct node {
    student* student;
    struct node* next;
    struct node* last;
}node;

student* head = NULL;  // first node
student* tail = NULL;  // last node

student* inputStudent(){
    char tmpnum[50];
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
    
    // FIXME produces segfault if user input is formatted wrongly
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
    s -> birthday.day = date[0];
    s -> birthday.month = date[1];
    s -> birthday.year = date[2];;

    printf("Geben sie ihren Vornamen ein:\n");
    fgets(s -> name, 50, stdin);

    printf("Geben sie ihren Nachnamen ein:\n");
    fgets(s -> surname, 50, stdin);
    
    // FIXME produces segfault if user input is formatted wrongly
    printf("Geben sie ihr vorraussichtliches Startdatum ein\n");
    fgets(tmpnum, 50, stdin);
    
    date[0] = atoi(strtok(tmpnum, "."));
    for(int i = 1; i < 3; i++){
        if(tmpnum[i] == ' '){
            break;
        }
        date[i] = atoi(strtok(NULL, "."));
    }   
    s -> startdate.day = date[0];
    s -> startdate.month = date[1];
    s -> startdate.year = date[2];;

    // FIXME produces segfault if user input is formatted wrongly
    printf("Geben sie ihr vorraussichtliches Abschlussdatum ein\n");
    fgets(tmpnum, 50, stdin);
    
    date[0] = atoi(strtok(tmpnum, "."));
    for(int i = 1; i < 3; i++){
        if(tmpnum[i] == ' '){
            break;
        }
        date[i] = atoi(strtok(NULL, "."));
    }   
    s -> enddate.day = date[0];
    s -> enddate.month = date[1];
    s -> enddate.year = date[2];;

    return s;
}

/*
void addNode(node* n){
    if(studentListLength == 0){
        // no elements in list yet, create the first.
        head = n;
    }
    else {
        tail->next = n;
        tail = n;
    }
    studentListLength++;
}
*/

void delNode(node* n){
    n->last->next = n->next;
    // TODO does free() work for our structs?
    free(n);
    studentListLength--;
}

// Schreibe eine Funktion in der die Anzahl der gespeicherten Studenten zurueck gegeben werden soll.
int getStudentenListLength(){
    return studentListLength;
}

void addStudent(student* s){ //FIXME Adresses in node wrong
    // TODO check if given student is already in the arr
    //node *n = (struct node*) malloc(sizeof(struct node));
    //n -> student = s;

    if(studentListLength == 0){
        // no elements in list yet, create the first.
        head = s;
        head -> last = s;
        tail = s;
    }
    else {
        // FIXME is this a good idea? might cause trouble when looping to find stuff
        // This seems like hacky and bad code.
        s -> next = NULL;
        //head -> last -> next = s;
        head -> last = s;
        tail = s;  
    }
    studentListLength++;
}

// Schreibe eine funktion deleteStudent(matrikelnummer), welche einen Studenten loescht.
// TODO rewrite with nodes
int deleteStudent(int mNum){
    // TODO iterate nodes, delete node with mNum matching argument
    // return 0 on success, 1 on fail
    student *inode = head;
    if(inode == tail && inode -> matriculationNumber == mNum){
        free(head);
        head = NULL;
        studentListLength--;
        return 0;
    }
    while(inode != tail){
        if(inode -> next -> matriculationNumber == mNum){
            free(inode -> next);
            inode -> next = NULL;
            inode -> next = inode -> next -> next;
            studentListLength--;
            return 0;
        }
        inode = inode -> next;
    }
    return 1;
}

int recursiveDestroy(student *del){
    /*
    printf("%x\n", head);
    printf("%x\n", tail);
    printf("%x\n", head -> last);
    */
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
    student *inode = head;
    if(studentListLength > 0 && inode != NULL){
        for (int i = 0; i < studentListLength; i++){
            printf("Name: %s", inode -> name);
            printf("Surname: %s", inode -> surname);
            printf("Age: %d\n", inode -> age);
            printf("Mnumber: %d\n", inode -> matriculationNumber);
            printf("Bithdate: %d.", inode -> birthday.day);
            printf("%d.", inode -> birthday.month);
            printf("%d\n", inode -> birthday.year);
            inode = inode -> next;
        }
    }
    /*
    else if (studentListLength == 1) {
        printf("%d", head -> student -> age);
    }
    */
}

struct date parseDate(char* cptr){
    struct date d;
    struct date* dptr = &d;
    char* part[3];   // TODO check if this is enough if names are fully filled.

    part[0] = strtok(cptr, ".");    // day
    part[1] = strtok(NULL, ".");    // month
    part[2] = strtok(NULL, ".");    // year

    dptr->day = atoi(part[0]);
    dptr->month = atoi(part[1]);
    dptr->year = atoi(part[2]);

    return d;
}

char* removeQuotes(char* cptr){
    char* cptrN = malloc(sizeof(cptr));    // TODO check if this works for full lenght char pointers!
    strcpy(cptrN, cptr);
    return cptrN;
}

int readCSVIntoMemory(){

    FILE* stream = fopen("student.csv", "r");

    char* line = malloc(sizeof(char)*1024);
    if(line==NULL){
        printf("Could not get memory!\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(line, 1024, stream))
    {
        char* removedQuotesString;
        char* part[7];   // TODO check if this is enough if names are fully filled.
        part[0] = strtok(line, ",");    // age
        part[1] = strtok(NULL, ",");    // birthday
        part[2] = strtok(NULL, ",");    // name
        part[3] = strtok(NULL, ",");    // surname
        part[4] = strtok(NULL, ",");    // matriculationNumber
        part[5] = strtok(NULL, ",");    // startdate
        part[6] = strtok(NULL, ",");    // enddate
        // Debug: print all segments
        printf("%s|%s|%s|%s|%s|%s|%s", part[0], part[1], part[2], part[3], part[4], part[5], part[6]);

        char tmp[50] = "Buggy read from file\n";
        student* s = malloc(sizeof(student));
        // TODO check if s is NULL
        s->age = atoi(part[0]);
        s->birthday = parseDate(part[1]);   // SIGSEV
        removedQuotesString = removeQuotes(part[2]);
        strcpy(s->name, removedQuotesString);
        removedQuotesString = removeQuotes(part[3]);
        strcpy(s->surname, removedQuotesString);
        // strcpy(s->name, tmp);
        // strcpy(s->surname, tmp);
        s->matriculationNumber = atoi(part[4]);
        s->startdate = parseDate(part[5]);
        s->enddate = parseDate(part[6]);

        printf("Name: %s\n", s -> name);
        printf("Surname: %s\n", s -> surname);
        printf("Age: %d\n", s -> age);
        printf("Mnumber: %d\n", s -> matriculationNumber);
        printf("Bithdate: %d.%d.%d\n", s -> birthday.day, s -> birthday.month, s -> birthday.year);
        printf("Startdate: %d.%d.%d\n", s -> startdate.day, s -> startdate.month, s -> startdate.year);
        printf("Enddate: %d.%d.%d\n\n", s -> enddate.day, s -> enddate.month, s -> enddate.year);
        // FIXME adding the done students doesn't work
        addStudent(s);

        // don't free s here, we will need it for as long as the process runs!
    }
    fclose(stream);
    free(line);
    return 0;
}

void printStudent(int Martik){
    student *inode = head;
    int fund=0;
    if(studentListLength > 0 && inode != NULL){
        for(int i=0;i<studentListLength;i++){
            if(Martik == inode ->matriculationNumber){
                printf("Name: %s", inode -> name);
                printf("Surname: %s", inode -> surname);
                printf("Age: %d\n", inode -> age);
                printf("Mnumber: %d\n", inode -> matriculationNumber);
                printf("Bithdate: %d.", inode -> birthday.day);
                printf("%d.", inode -> birthday.month);
                printf("%d\n", inode -> birthday.year);
                fund=1;
            }
        }
        if(fund==0){
            printf("Unter dieser Martikulartionsnummer ist kein Student gespeichert.");
        }
    }
}

int main(){
    int ende =0;
    int wahl;

    // read all students from student.csv
    // is a buggy mess.
    readCSVIntoMemory();
    // FIXME DEBUG PAUSING
    getc(stdin);

    do{
        printf("\e[1;1H\e[2J");
        printf("Bitte Wahl treffen:\n");
        printf("(1) Neuen Studenten anlegen\n");
        printf("(2) Anzahl der gespeicherten Studenten abrufen\n");
        printf("(3) Student anhand der Martikelnummer ausgeben\n");
        printf("(4) Alle Studenten alphabetisch ausgeben\n");
        printf("(5) Studenten loeschen\n");
        printf("(6) Programm beenden\n");
        char tmpnum[50];
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
                printf("Matrikulationsnummer eingeben");
                fgets(tmpnum, 50, stdin);
                deleteStudent(atoi(tmpnum));
                break;
            case 6:
                recursiveDestroy(head);
                ende=1;
                break;
            default:
                printf("Bitte einen gueltigen Wert eingeben\n");
        }
        // FIXME it would be good practice to use the same input function for all inputs
        //char buf[1];
        //fgets(buf , 1, stdin);
        getc(stdin);
    }while (ende!=1);
    printf("Auf Wiedersehen\n");
    return 0;
}
