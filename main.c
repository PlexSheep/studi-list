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
typedef struct {
    int age;
    struct date birthday;
    char name[50];
    char surname[50];
    int matriculationNumber;
    struct date startdate;
    struct date enddate;
}student;

// make a global var to store all of our students. This is a pointer because we want to use malloc()
int studentListLength = 0;

typedef struct node {
    student* student;
    struct node* next;
    struct node* last;
}node;

node* head = NULL;  // first node
node* tail = NULL;  // last node

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
    node *n = (struct node*) malloc(sizeof(struct node));
    n -> student = s;

    if(studentListLength == 0){
        // no elements in list yet, create the first.
        head = n;
        head -> last = n;
        tail = n;
    }
    else {
        n -> next = NULL;
        head -> last -> next = n;
        head -> last = n;
        tail = n;  
    }
    studentListLength++;
}

// Schreibe eine funktion deleteStudent(matrikelnummer), welche einen Studenten loescht.
// TODO rewrite with nodes
int deleteStudent(int mNum){
    // TODO iterate nodes, delete node with mNum matching argument
    // return 0 on success, 1 on fail
    return 0;
}

int recursiveDestroy(node *del){
    /*
    printf("%x\n", head);
    printf("%x\n", tail);
    printf("%x\n", head -> last);
    */
    if(del == tail){
        //printf("Deleted until head\n"); //DEBUG:
        free(del -> student);
        free(del);
    }
    else {
        recursiveDestroy(del -> next);
        free(del -> student);
        free(del);
    }
    return 0;
}

void printAllStudents(){
    if(studentListLength > 0){
        node *inode = head;
        for (int i = 0; i < studentListLength; i++){
            printf("Name: %s", inode -> student -> name);
            printf("Surname: %s", inode -> student -> surname);
            printf("Age: %d\n", inode -> student -> age);
            printf("Mnumber: %d\n", inode -> student -> matriculationNumber);
            printf("Bithdate: %d.", inode -> student -> birthday.day);
            printf("%d.", inode -> student -> birthday.month);
            printf("%d\n", inode -> student -> birthday.year);
            inode = inode -> next;
        }
    }
    /*
    else if (studentListLength == 1) {
        printf("%d", head -> student -> age);
    }
    */
}


int main(){
    int ende =0;
    int wahl;

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
                //printStudent();
                break;
            case 4:
                printf("\e[1;1H\e[2J");
                printAllStudents();
                break;
            case 5:
                printf("\e[1;1H\e[2J");
                //deleteStudent();
                break;
            case 6:
                recursiveDestroy(head);
                printf("%x", head);
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
