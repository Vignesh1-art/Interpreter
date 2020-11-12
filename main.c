#include<stdio.h>
#include<stdlib.h>
#include "parser.h"
#include "ast.h"
#include "datastructure.h"
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
root=root->next;
printf("%d",root->type);
}
