#include <stdio.h>
#include "symtable.h"

int main (int argc, char** argv) {
    initSymTable();

    char id[100];
    printf("Enter identifier: ");
    scanf("%s", id);
    while (strcmp(id, "q") != 0) {
        printf("The scan was %s\n", id);
        if (!addSymbol(id)) {
            printf("%s added\n", id);
        } else {
            printf("%s colide\n", id);
        }
        printf("Enter identifier: ");
        scanf("%s", id);
    }
    printSymTable();
    disposeSymTable();

    return 0;
}