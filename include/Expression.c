#include<stdio.h>
#include "Expression.h"
#include "datastructure.h"
#include "ast.h"

///Here expression tree construction managed
void init_node_stack(){
node_stack.top=-1;
}

void push_to_node_stack(struct AST_NODE *item){
if(node_stack.top>20-1){
    //printf("Expression size too much %d\n",node_stack.top);
    exit(0);
}
node_stack.top++;
node_stack.items[node_stack.top]=item;
}

struct AST_NODE *pop_from_node_stack(){
if(node_stack.top<0){
    printf("Underflow in expression stack\n");
    exit(0);
}
//printf("Popping %d\n",node_stack.items[node_stack.top]->type);
node_stack.top--;
return node_stack.items[node_stack.top+1];
}

struct AST_NODE *create_exp_tree_from_q(){
for(int i=0;i<=q.f;i++){
    enum TokenType type=q.nodeq[i].type;
    if(type==const_num){
        struct AST_NODE *node=create_numeric_binode(toint(q.nodeq[i].lexeme));
        push_to_node_stack(node);
    }
    else if(type==identifier)
    {
        struct AST_NODE *node=create_variable_binode(q.nodeq[i].lexeme);
        push_to_node_stack(node);
    }
    else{

        struct AST_NODE *node=create_binary_node(type);

        node->children[1]=pop_from_node_stack();
        node->children[0]=pop_from_node_stack();
        push_to_node_stack(node);
    }

}
if(node_stack.top!=1){
    printf("Expression invalid %d\n",node_stack.top);
    exit(0);
}
return pop_from_node_stack();
}

void traverse_tree(struct AST_NODE *root){
if(root==0)
    return;
traverse_tree(root->children[0]);
printf("%d\n",root->type);
traverse_tree(root->children[1]);
}

int eval_tree(struct AST_NODE *root){
    init_node_stack();
if(root==0)
    return 0;
if(root->children[0]==0 && root->children[1]==0){
    int *a=root->content;
    return *a;
}
int l_val=eval_tree(root->children[0]);
int r_val=eval_tree(root->children[1]);
switch(root->type){
case _add:return (l_val+r_val);
case _sub:return (l_val-r_val);
case _mult:return (l_val*r_val);
case _div:return (l_val/r_val);
}
}


