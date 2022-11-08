#ifndef __AST_H
#define __AST_H

struct ast {
    int nodetype;
    struct ast *l;
    struct ast *r;
};

struct instval {
    int nodetype;
    struct symbol* s;
    struct ast *v;
};

struct ast* newinstval(struct symbol* s, struct ast* v);

void treefree(struct ast*);

#endif