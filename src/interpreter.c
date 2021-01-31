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

int eval_tree(struct AST_NODE *root){
if(root==0)
    return 0;
if(root->children[0]==0 && root->children[1]==0)
{
    int *a;
    if(root->type==identifier)
        *a=get_int(root->content);
    else
        a=root->content;
    return *a;
}
int l_val=eval_tree(root->children[0]);
int r_val=eval_tree(root->children[1]);
switch(root->type)
{
case _add:return (l_val+r_val);
case _sub:return (l_val-r_val);
case _mult:return (l_val*r_val);
case _div:return (l_val/r_val);
}
}

void interpret_equals(struct AST_NODE *root)
{
    if(root==0)
        return;
  struct AST_NODE *var=root->children[0];
  struct AST_NODE *right_child=root->children[1];
  char *s=var->content;
  if(right_child->type==_add || right_child->type==_mult || right_child->type==_sub || right_child->type==_div)
  {
    int a=eval_tree(right_child);
  }
  interpret_equals(root->next);
}
