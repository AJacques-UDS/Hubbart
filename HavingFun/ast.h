#ifndef __AST_H
#define __AST_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef enum __node_type {
    IDENTIFIER_NODE,
    DATATYPE_NODE,
    VALUE_NODE
} node_type;

typedef struct node_s {
    node_type type;
    void* node_data;
    struct node_s ** children;
} node_t;


node_t* init_identifier(const char *);
node_t* init_value(const char *);
node_t* init_type(const char *);

#endif