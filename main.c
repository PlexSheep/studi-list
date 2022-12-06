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

    //Check if student struct has been assigned a memory region
    if(s == NULL){
        exit(EXIT_FAILURE);
    }

    printf("Geben sie ihr Alter ein:\n");
    fgets(tmpnum, 50, stdin);
    s -> age = atoi(tmpnum);

    printf("Geben sie ihre Matrikelnummer ein\n");
    fgets(tmpnum, 50, stdin);
    s -> matriculationNumber = atoi(tmpnum);
    
    printf("Geben sie ihr Geburtsdatum ein:\n");
    fgets(tmpnum, 50, stdin);
    int date[3];

    // Code to split string that contains '.' characters (dates)
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
    
    printf("Geben sie ihr vorraussichtliches Startdatum ein\n");
    fgets(tmpnum, 50, stdin);
    
    // Code to split string that contains '.' characters (dates)
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

/*
void delNode(node* n){
    n->last->next = n->next;
    // TODO does free() work for our structs?
    free(n);
    studentListLength--;
}
*/
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
        head -> last = s;
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
            head = s -> next;
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

    // If this case is true, it is either the last oronly element in the list and the method should terminate once it is freed
    if(inode == tail && inode -> matriculationNumber == mNum){
        free(head);
        head = NULL;
        studentListLength--;
        return 0;
    }

    // If above condition is not met, below code walks through the list and checks for the matchning matriculation number.
    // If match is found, code frees and NULL's the matche
    while(inode -> next -> matriculationNumber == mNum && inode != NULL){
        inode = inode -> next;
    }
    free(inode -> next);
    inode -> next = NULL;
    inode -> next = inode -> next -> next;
    studentListLength--;
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


int main(){
    /*
    ########################################################################
    # The main method takes care of the menu and menu                      #
    # user input functionality                                             #
    ########################################################################
    */
    int ende =0;
    int wahl;

    do{
        printf("\e[1;1H\e[2J"); // This is the ANSI escape sequence to clear the terminal and set coursor to start position. Used for fancy TUI
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
                printf("Matrikulationsnummer eingeben");
                fgets(tmpnum, 50, stdin);
                deleteStudent(atoi(tmpnum));
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
