#include<stdio.h>
#include "datastructure.h"
#include "ast.h"
int toint(char *n){
    int num=0;
for(int i=0;n[i]!=0;i++){
    int temp=n[i]-'0';
    num=num*10+temp;
}
return num;
}


struct AST_NODE *create_ast(struct Token t){
struct AST_NODE *x=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
x->type=t.type;
x->next=0;
x->content=t.lexeme;
return x;
}

struct AST_NODE *create_binary_node(enum TokenType op){
struct AST_NODE *x=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
x->type=op;
x->next=0;
x->children=(struct AST_NODE *)malloc(2*sizeof(struct AST_NODE *));
x->children[0]=0;
x->children[1]=0;
return x;
}


struct AST_NODE *create_numeric_binode(int number){
int *x=(int)malloc(sizeof(int));
*x=number;
struct AST_NODE *node=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
node->children=(struct AST_NODE *)malloc(2*sizeof(struct AST_NODE *));
node->children[0]=0;
node->children[1]=0;
node->type=const_num;
node->content=x;
return node;
}

struct AST_NODE *create_if_node(){
struct AST_NODE *node=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
node->type=_if;
node->children=(struct AST_NODE *)malloc(3*sizeof(struct AST_NODE *));
node->children[0]=0;
node->children[1]=0;
node->children[2]=0;
return node;
}

struct AST_NODE *create_variable_binode(char *name)
{
struct AST_NODE *node=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
node->type=identifier;
node->children=(struct AST_NODE *)malloc(2*sizeof(struct AST_NODE *));
node->children[0]=0;
node->children[1]=0;
node->content=(void *)name;
return node;
}

