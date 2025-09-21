/***********************
 * Michael Ellis
 * mje2@clemson.com
 * Lab 5 and Lab Section 3 
 **********************/

#include <stdio.h>

struct NODE{
    int a;
    struct NODE *b;
    struct NODE *c;
}nodes[5] = { 
                {15,    nodes + 2, nodes+1},
                {30,    nodes + 3, NULL},
                {46,    nodes + 1,  nodes + 4},
                {95,    nodes + 4,  nodes},
                {123,   NULL, nodes + 2}
    };
struct NODE* np = nodes + 4;
struct NODE** npp = &nodes[2].b;

int main()
{
    // printing each statement that is legal. (atleast legal in my docx.)
    printf("nodes\t\t%p\n", nodes);
    // nodes.a is ILLEGAL
    printf("nodes[3].a\t%d\n", nodes[3].a);
    printf("nodes[3].c\t%p\n", nodes[3].c);
    printf("nodes[3].c->a\t%d\n", nodes[3].c->a);
    // *nodes.a is ILLEGAL
    printf("(*nodes).a\t%d\n", (*nodes).a);
    // nodes->a is ILLEGAL
    printf("nodes[3].b->b\t%p\n", nodes[3].b->b);
    printf("&nodes[3].a\t%p\n", &nodes[3].a);
    printf("&nodes[3].c\t%p\n", &nodes[3].c);
    printf("&nodes[3].c->a\t%p\n", &nodes[3].c->a);
    // &nodes->a is ILLEGAL
    printf("np\t\t%p\n", np);
    printf("np->a\t\t%d\n", np->a);
    printf("np->c->c->a\t%d\n", np->c->c->a);
    printf("npp\t\t%p\n", npp);
    // npp->a is ILLEGAL
    printf("*npp\t\t%p\n", *npp);
    // *npp->a is ILLEGAL
    printf("(*npp)->a\t%d\n", (*npp)->a);
    printf("&np\t\t%p\n", &np);
    printf("&np->a\t\t%p\n", &np->a);
    printf("&np->c->c->a\t%p\n", &np->c->c->a);   

    return 0;

}

