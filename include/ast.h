#ifndef __AST_H
#define __AST_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "symtable.h"

typedef enum __node_type {
    IMPORTATION_NODE,

    IDENTIFIER_NODE,
    IMPORT_KW_NODE,
    INT_KW_NODE,
    FLOAT_KW_NODE,
    FROM_KW_NODE,

    INTEGER_LITERAL_NODE,
    FLOAT_LITERAL_NODE,

    INSTANTIATION_NODE,

    FACTOR_NODE,
    ASSIGN_NODE
} node_type;

struct node_t {
    node_type type;
    void *node_data;
    struct node_t **children;
};

struct node_t *ast_init_importation(struct node_t *, struct node_t *);

struct node_t *ast_init_identifier(const char *);
struct node_t *ast_init_kw(const char *);

struct node_t *ast_init_integer(const char *);
struct node_t *ast_init_float(const char *);

struct node_t *ast_init_instantiate(struct node_t *, struct node_t *, struct node_t *);

struct node_t *ast_init_arith_op(struct node_t *, char *, struct node_t *);
struct node_t *ast_init_assign(struct node_t *, struct node_t *);

#endif
