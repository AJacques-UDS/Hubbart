#include <stdio.h>
#include "ast.h"

int main (int argc, char** argv) {
    node_t* id;
    node_t* val;
    node_t* type;

    id = init_identifier("age");
    val = init_value("40");
    type = init_type("int");

    printf("The %s of type %s with value %s.\n", (char *)id->node_data, (char *)type->node_data, (char *)val->node_data);

    void* v_id;
    void* v_val;
    void* v_type;

    void* v[3];

    v[0] = init_identifier("age");
    v[1] = init_value("40");
    v[2] = init_type("int");

    for (int i = 0; i < 3; i++) {
        node_type* t = (node_type *)v[i];

        if (t != NULL) {
            switch (*t) {
            case IDENTIFIER_NODE:
                printf("The node is an identifier.\n");
                break;
            case VALUE_NODE:
                printf("The node is a value.\n");
                break;
            case DATATYPE_NODE:
                printf("The node is a data type.\n");
                break;
            default:
                printf("Error.\n");
                break;
            }
        }
    }

    return 0;
}