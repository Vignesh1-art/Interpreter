#ifndef AST
#define AST
struct AST_NODE *create_ast();

struct AST_NODE *create_binary_exp_node(enum TokenType);


struct AST_NODE *create_numeric_binode(int ,enum TokenType);//For expression tree


struct AST_NODE *create_if_node();
#endif // AST
