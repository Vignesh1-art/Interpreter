#ifndef AST
#define AST
#include "datastructure.h"
struct AST_NODE{
    enum TokenType type;
    void *content;
    struct AST_NODE **children; //Array of children
    struct AST_NODE *next;//Pointer to next sibling
};
struct AST_NODE *create_ast(struct Token t);

struct AST_NODE *create_binary_exp_node(enum TokenType);


struct AST_NODE *create_numeric_binode(int);//For expression tree

struct AST_NODE *create_variable_binode(char *name);

struct AST_NODE *create_if_node();
#endif // AST
