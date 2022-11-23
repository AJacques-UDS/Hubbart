#include <stdio.h>
#include "ast.h"

int main (int argc, char **argv) {

    char *from = "from";
    struct node_t *n_from = ast_init_kw(from);

    char *type = "float";
    struct node_t *n_type = ast_init_type(type);

    char *id = "cost";
    struct node_t *n_id = ast_init_identifier(id);

    char *val = "3.16";
    struct node_t *n_val = ast_init_value(val);

    struct node_t *n_inst = ast_init_inst(n_id, n_type, n_val);

    for (int i = 0; i < 3; i++) {
        struct node_t *n = n_inst->children[i];
        switch(n->type) {
        case IDENTIFIER_NODE:
            printf("An identifier\n");
            printf("%s\n", (char *)n->node_data);
            break;
        case DATATYPE_NODE:
            printf("A type\n");
            printf("%s\n", (char *)n->node_data);
            break;
        case VALUE_NODE:
            printf("A value\n");
            printf("%s\n", (char *)n->node_data);
            break;
        default:
            printf("Invalid type\n");
            break;
        }
    }

    printf("Freeing the nodes...\n");
    free(n_from);
    free(n_type);
    free(n_id);
    free(n_val);
    free(n_inst);

    return 0;
}
