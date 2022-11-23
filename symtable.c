#include "symtable.h"

static symbol** symbols;
static int size;

static symbol* previousNode;
static symbol* currentNode;

void initHashElement(const char *id) {
    int hash = hashSymbol(id);
    if (symbols[hash] == NULL) {
        symbols[hash] = (symbol*)malloc(sizeof(symbol));
        symbols[hash]->identifier = (char*)malloc(sizeof(char) * strlen(id));
        strcpy(symbols[hash]->identifier, id);
        symbols[hash]->next = NULL;
    }
}

void initSymbol(const char* id) {
    if (currentNode->next == NULL) {
        currentNode->next = (symbol*)malloc(sizeof(symbol));
        currentNode->next->identifier = (char*)malloc(sizeof(char) * strlen(id));
        strcpy(currentNode->next->identifier, id);
        currentNode->next->next = NULL;
    }
}

void initSymTable(void) {
    size = 0;
    symbols = (symbol **)malloc(sizeof(symbol *) * SYMTABLE_MAX_SIZE);
    for (int i = 0; i < SYMTABLE_MAX_SIZE; i++) {
        symbols[i] = NULL;
    }
}

void disposeSymbol(symbol* s) {
    if (s->next != NULL) {
        disposeSymbol(s->next);
    }
    free(s->identifier);
    free(s);
}

void disposeSymTable(void) {
    if (symbols == NULL) {
        return;
    }
    for (int i = 0; i < SYMTABLE_MAX_SIZE; i++) {
        if (symbols[i] != NULL) {
            disposeSymbol(symbols[i]);
        }
    }
    free(symbols);
}

int hashSymbol(const char* id) {
    if (symbols == NULL) {
        return -1;
    }

    int size = strlen(id);
    int total = 0;

    for (int i = 0; i < size; i++) {
        total += (int)id[i];
    }

    return total % SYMTABLE_MAX_SIZE;
}

static void __addSymbol(const char* id) {
    int hash = hashSymbol(id);
    if (symbols[hash] == NULL) {
        initHashElement(id);
        size++;
    } else {
        previousNode = symbols[hash];
        char found = 0;
        while (!found && previousNode != NULL) {
            if (strcmp(previousNode->identifier, id) == 0) {
                found = 1;
            } else {
                currentNode = previousNode;
                previousNode = previousNode->next;
            }
        }
        if (!found && previousNode == NULL && currentNode != NULL) {   
            initSymbol(id);
            size++;
        }
    }
}

short addSymbol(const char* id) {
    if (symbols == NULL) {
        return -1;
    }

    __addSymbol(id);

    int hash = hashSymbol(id);
    return 0;
}

void printSymTable(void) {
    printf("Content of the Symbol's Table\n\n");

    if (size == 0) {
        printf("The symtable is empty\n");
    } else {
        for (int i = 0; i < SYMTABLE_MAX_SIZE; i++) {
            symbol* current = symbols[i];
            printf("%d - \n", i);

            while (current != NULL) {
                printf("Symbol %s\n", current->identifier);
                current = current->next;
            }
            printf("\n");
        }
    }

    printf("\nEnd of Content\n\n");
}
