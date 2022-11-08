#include "ast.h"

static void* currentNode;
static int currentType;

/*
typedef struct node_s {
    node_type type;
    void* node_data;
    node_s** child;
} node_t;
*/

node_t* init_identifier(const char* content) {
    node_t* node = (node_t *)malloc(sizeof(node_t));

    node->type = IDENTIFIER_NODE;
    char* name = (char *)malloc(sizeof(char) * strlen(content));
    strcpy(name, content);
    node->node_data = (void *)name;

    return node;
}

node_t* init_value(const char* content) {
    node_t* node = (node_t *)malloc(sizeof(node_t));

    node->type = IDENTIFIER_NODE;
    char* name = (char *)malloc(sizeof(char) * strlen(content));
    strcpy(name, content);
    node->node_data = (void *)name;

    return node;
}

node_t* init_type(const char* content) {
    node_t* node = (node_t *)malloc(sizeof(node_t));

    node->type = IDENTIFIER_NODE;
    char* name = (char *)malloc(sizeof(char) * strlen(content));
    strcpy(name, content);
    node->node_data = (void *)name;

    return node;
}