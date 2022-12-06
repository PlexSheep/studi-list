#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
    if(argc < 2)
        exit(EXIT_FAILURE);
    int date[3] = { -1, -1, -1 };
    char* cptr;
    printf("%s\n", argv[1]);
    cptr = strtok(argv[1], ".");
    printf("%s\n", cptr);
    date[0] = atoi(cptr);
    cptr = strtok(NULL, ".");
    printf("%s\n", cptr);
    date[1] = atoi(cptr);
    cptr = strtok(NULL, ".");
    printf("%s\n", cptr);
    date[2] = atoi(cptr);

    printf("%d.%d.%d\n", date[0], date[1], date[2]);

    return 0;
}
