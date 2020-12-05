#include "datastructure.h"
#include "variable.h"
#include "ast.h"

void init_interpreter()
{
    init_variable();
}

void interpret(struct AST_NODE *root)
{
    switch(root->type)
    {
        case _equal:interpret_equals(root);
    }
}

void interpret_equals(struct AST_NODE *root)
{
  struct AST_NODE *var=root->children[0];
  char *s=var->content;
  int *x=(int *)malloc(sizeof(int));
  struct Variable *v=create_variable(_int,x);
  define_variable(s,v);
}
