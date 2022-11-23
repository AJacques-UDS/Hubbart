#ifndef __AST_H
#define __AST_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "symtable.h"

typedef enum __node_type {
    ROOT_NODE,
    IDENTIFIER_NODE,
    DATATYPE_NODE,
    VALUE_NODE,
    INSTANTIATE_NODE,
    KEYWORD_NODE,
    IMPORT_NODE,
    FROM_NODE
} node_type;

struct node_t {
    node_type type;
    void *node_data;
    struct node_t **children;
};

void init_ast(struct node_t *);

struct node_t *ast_init_inst(struct node_t *, struct node_t *, struct node_t *);
struct node_t *ast_init_import(struct node_t *, struct node_t *);
struct node_t *ast_init_from(struct node_t *);

struct node_t *ast_init_identifier(const char *);
struct node_t *ast_init_value(const char *);
struct node_t *ast_init_type(const char *);
struct node_t *ast_init_kw(const char *);

void print_node(struct node_t *);
void delete_tree(struct node_t *);

#endif
