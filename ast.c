#include "ast.h"

void init_ast(struct node_t *n) {
    n = (struct node_t *)malloc(sizeof(struct node_t));
    n->type = ROOT_NODE;
}

static struct node_t *init_with_str(const char *content, node_type t) {
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = t;
    char *name = strdup(content);
    node->node_data = (void *)name;

    return node;
}

struct node_t *ast_init_inst(struct node_t *id, struct node_t *type, struct node_t *val) {
    if (id->type != IDENTIFIER_NODE && type->type != DATATYPE_NODE && val->type != VALUE_NODE) {
        fprintf(stderr, "Didn't receive proper nodes.\n");
        return NULL;
    }

    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = INSTANTIATE_NODE;
    node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 3);

    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[1] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[2] = (struct node_t *)malloc(sizeof(struct node_t));

    node->children[0] = id;
    node->children[1] = type;
    node->children[2] = val;

    return node;
}

//@TODO Redo pointer assignation
struct node_t *ast_init_import(struct node_t *id, struct node_t *from) {
    if (id->type != IDENTIFIER_NODE && (from == NULL || from->type != KEYWORD_NODE)) {
        fprintf(stderr, "%d - %d\n", id->type, from->type);
        fprintf(stderr, "Didn't receive proper nodes.\n");
        return NULL;
    }
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = IMPORT_NODE;
    node->children = (struct node_t **)malloc(sizeof(struct node_t *) * 2);
    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[1] = (struct node_t *)malloc(sizeof(struct node_t));

    node->children[0]->type = id->type;
    node->children[1] = from;

    return node;
}

struct node_t *ast_init_from(struct node_t *id) {
    if (id->type != IDENTIFIER_NODE) {
        fprintf(stderr, "Didn't receive proper nodes.\n");
        return NULL;
    }
    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));

    node->type = FROM_NODE;
    node->children = (struct node_t **)malloc(sizeof(struct node_t *));
    node->children[0] = (struct node_t *)malloc(sizeof(struct node_t));
    node->children[0]->type = id->type;
    node->children[0]->node_data = (char *)strdup(id->node_data);

    return node;
}

struct node_t *ast_init_identifier(const char *content) {
    return init_with_str(content, IDENTIFIER_NODE);
}

struct node_t *ast_init_value(const char *content) {
    return init_with_str(content, VALUE_NODE);
}

struct node_t *ast_init_type(const char *content) {
    return init_with_str(content, DATATYPE_NODE);
}

struct node_t *ast_init_kw(const char *content) {
    return init_with_str(content, KEYWORD_NODE);
}

void delete_tree(struct node_t *n) {
    switch(n->type) {
        case INSTANTIATE_NODE:
            break;
        case IMPORT_NODE:
            delete_tree(n->children[0]);
            delete_tree(n->children[1]);
            free(n->children);
        case FROM_NODE:
            delete_tree(n->children[0]);
            delete_tree(n->children[1]);
            free(n->children);
            break;
        case KEYWORD_NODE:
        case DATATYPE_NODE:
        case VALUE_NODE:
        case IDENTIFIER_NODE:
            free((char *)n->node_data);
            break;
        default:
            break;
    }
}


void print_node(struct node_t *n) {
    switch (n->type) {
        case ROOT_NODE:
            printf("Root node");
            break;
        case IDENTIFIER_NODE:
            printf("Identifier node\n");
            printf("%s", (char *)n->node_data);
            break;
        case DATATYPE_NODE:
            printf("Datatype node\n");
            break;
        case VALUE_NODE:
            printf("Value node\n");
            printf("%s", (char *)n->node_data);
            break;
        case INSTANTIATE_NODE:
            printf("Instantiate node\n");
            break;
        case KEYWORD_NODE:
            printf("Keyword node\n");
            break;
        case IMPORT_NODE:
            printf("Import node\n");
            break;
        case FROM_NODE:
            printf("From node\n");
            break;
    }
}