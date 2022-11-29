#include "ast.h"

static struct node_t *init_with_str(const char *, node_type);

static struct node_t *init_with_str(const char *content, node_type t) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = t;
    char *name = strdup(content);
    node->node_data = (void *)name;

    return node;
}

struct node_t *ast_init_importation(struct node_t *import, struct node_t *from) {
    if (import->type != IDENTIFIER_NODE) {
        exit(1001);
    }

    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    node->type = IMPORTATION_NODE;
    
    if (from != NULL && from->type == IDENTIFIER_NODE) {
        node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 2);
        node->children[1] = from;
    } else if (from->type != IDENTIFIER_NODE) {
        exit(1011);
    } else {
        node->children = (struct node_t **)malloc(sizeof(struct node_t *));
    }

    node->children[0] = import;
    return node;
}

struct node_t *ast_init_identifier(const char *content) {
    return init_with_str(content, IDENTIFIER_NODE);
}

struct node_t *ast_init_kw(const char *content) {
    if (strcmp(content, "from") == 0) {
        return init_with_str(content, FROM_KW_NODE);
    } else if (strcmp(content, "import") == 0) {
        return init_with_str(content, IMPORT_KW_NODE);
    } else if (strcmp(content, "int") == 0) {
        return init_with_str(content, INT_KW_NODE);
    } else if (strcmp(content, "float") == 0) {
        return init_with_str(content, FLOAT_KW_NODE);
    } else {
        exit(1);
    }
}

struct node_t *ast_init_integer(const char *val) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = INTEGER_LITERAL_NODE;
    int *name = (int *)malloc(sizeof(int));
    *name = atoi(val);
    node->node_data = (void *)name;

    return node;
}

struct node_t *ast_init_float(const char *val) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = FLOAT_LITERAL_NODE;
    double *name = (double *)malloc(sizeof(double));
    *name = atof(val);
    node->node_data = (void *)name;

    return node;
}

struct node_t *ast_init_instantiate(struct node_t *id, struct node_t *type, struct node_t *literal) {
    if (id->type != IDENTIFIER_NODE) exit(2001);
    if (!(type->type == INT_KW_NODE || type->type == FLOAT_KW_NODE)) exit(2002);
    if (!(literal->type == INTEGER_LITERAL_NODE || literal->type == FLOAT_LITERAL_NODE)) exit(2003);

    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    node->type = INSTANTIATION_NODE;

    node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 3);
    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[1] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[2] = (struct node_t *)malloc(sizeof(struct node_t));

    node->children[0] = id;
    node->children[1] = type;
    node->children[2] = literal;

    return node;
}

struct node_t *ast_init_arith_op(struct node_t *term, char *op, struct node_t *factor) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    node->type = FACTOR_NODE;

    if (op != NULL) {
        char *operator = strdup(op);
        node->node_data = (void *)operator;
    }

    node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 2);
    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[1] = (struct node_t *)malloc(sizeof(struct node_t));

    node->children[0] = term;
    node->children[1] = factor;

    return node;
}

struct node_t *ast_init_assign(struct node_t *id, struct node_t *arith) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    node->type = ASSIGN_NODE;

    node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 2);
    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[1] = (struct node_t *)malloc(sizeof(struct node_t));

    node->children[0] = id;
    node->children[1] = arith;

    return node;
}