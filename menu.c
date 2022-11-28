int menu(){
    int ende =0;
    int wahl;

    printf("(1) Neuen Studenten anlegen\n");
    printf("(2) Anzahl der gespeicherten Studenten abrufen\n");
    printf("(3) Student anhand der Martikelnummer ausgeben\n");
    printf("(4) Alle Studenten alphabetisch ausgeben\n");
    printf("(5) Studenten loeschen\n");
    printf("(6) Programm beenden\n");

    do{
        printf("Bitte Wahl treffen: ");
        scanf_s("%d,&wahl");

        switch(wahl){
            case 1:
                addStudent();
                break;
            case 2:
                anzahl();
                break;
            case 3:
                printStudent();
                break;
            case 4:
                printAllStudents();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                ende=1;
                break;
            default:
                printf("Bitte einen gueltigen Wert eingeben");
        }
    }while (ende!=1);
    printf("Auf Wiedersehen");
    return 0;
}