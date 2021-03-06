#include<stdio.h>
#include<stdlib.h>
#include "parser.h"
#include "ast.h"
#include "datastructure.h"
#include "variable.h"
#include "interpreter.h"
#define DEV_MODE
void traver(struct AST_NODE *root)
{
    if(root==0)
        return;
    if(root->type==identifier)
    printf("%s\n",root->content);
    traver(root->children[0]);
    traver(root->children[1]);
}

main(int argc, char *argv[])
{
FILE    *infile;
char    *buffer;
long    numbytes;
#ifdef DEV_MODE
infile = fopen("t.txt", "r");
#else
infile = fopen(argv[1], "r");
#endif // DEV_MODE

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
init_interpreter();
interpret(root);
return 0;
}
