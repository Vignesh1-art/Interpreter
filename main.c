#include<stdio.h>
#include<stdlib.h>
#include "parser.h"
#include "ast.h"
#include "datastructure.h"
#include "variable.h"
void traver(struct AST_NODE *root)
{
    if(root==0)
        return;
    if(root->type==identifier)
    printf("%s\n",root->content);
    traver(root->children[0]);
    traver(root->children[1]);
}

main(){
FILE    *infile;
char    *buffer;
long    numbytes;

infile = fopen("t.txt", "r");
if(infile == NULL)
    return 2;
fseek(infile, 0L, SEEK_END);
numbytes = ftell(infile);

fseek(infile, 0L, SEEK_SET);

buffer = (char*)calloc(numbytes, sizeof(char));

if(buffer == NULL)
    return 1;

fread(buffer, sizeof(char), numbytes, infile);
fclose(infile);

init_parser(buffer);
struct AST_NODE *root=statements();
int t=9;
init_variable();
struct Variable *x=create_variable(_int,&t);
define_variable("anme",x);
x=get_variable("anme");
int *g=x->value;
printf("%d",*g);
}
