#include<stdio.h>
#include<string.h>

#include "Tokenizer.h"
#include "datastructure.h"
#include "ast.h"
#include "Expression.h"
#include "parser.h"
struct Token curr_tok,prev_tok;
struct AST_NODE temp_node,root;



int  is_curr_tok_bioperator(){
    if(curr_tok.type==_add || curr_tok.type==_mult || curr_tok.type==_div || curr_tok.type==_sub || curr_tok.type==mod)
        return 1;
    return 0;
}
int get_precedence(enum TokenType op){
if(op==_mult || op==_div || op==mod)
    return 2;
if(op==_add || op==_sub)
    return 1;
return -1;
}

void next_token(){
prev_tok=curr_tok;
curr_tok=get_token();
/*printf("Tok type :%d\n",curr_tok.type);
printf("Tok value :%s\n",curr_tok.lexeme);
*/
}
void init_parser(char *input){
init_tokenizer(input);
next_token();
}
int accept(enum TokenType t){
if(t==curr_tok.type){
    next_token();
    return 1;
}
return 0;
}

int expect(enum TokenType t,char *emsg){
if(accept(t))
return 1;
printf("%s at line %d\n",emsg,curr_tok.line+1);
exit(0);
}

int _expect(enum TokenType t,char *emsg){
///This expects token skipping next line
while(accept(next_line));
if(accept(t))
    return 1;
printf("%s at line %d\n",emsg,curr_tok.line+1);
exit(0);
}

void error(char *emsg){
printf("%s at line %d\n",emsg,curr_tok.line);
//printf("%d\n",curr_tok.type);
exit(0);
}

void expr(){
if(accept(identifier) || accept(const_num)){
    insert_to_Tokq(prev_tok);
    if(is_curr_tok_bioperator()){
        if(!is_stack_empty() && get_precedence(curr_tok.type)<get_precedence(top_stack().type)){
            insert_to_Tokq(pop_from_token_stack());
            push_to_token_stack(curr_tok);
        }
        else{
        push_to_token_stack(curr_tok);
        }
        next_token();
        expr();
        }
    else if(curr_tok.type!=close_brac && curr_tok.type!=next_line && curr_tok.type!=EOP){
        error("Syntax error in expression:Bracket mismatch or expecting operator");
    }
}
else if(accept(open_brac)){
    push_to_token_stack(prev_tok);
    expr();
    expect(close_brac,"Expecting )");
    while(top_stack().type!=open_brac)
        insert_to_Tokq(pop_from_token_stack());
    pop_from_token_stack();
if(is_curr_tok_bioperator()){
    push_to_token_stack(curr_tok);
    next_token();
    expr();
}
}
else if(accept(next_line) || accept(EOP)){
;
}
else{
error("Invalid token in expression");
}

}

struct AST_NODE *expression()
{
init_queue();
init_tok_stack();
expr();
while(!is_stack_empty()){
insert_to_Tokq(pop_from_token_stack());
}
struct AST_NODE *r=create_exp_tree_from_q();
return r;
}

struct AST_NODE *condition(){
    ///Root type: compare operater
    struct AST_NODE *temp,*cond;
if(accept(identifier) || accept(const_num)){
    temp=create_ast(prev_tok);
    if(accept(greaterthan_or_equal) || accept(lessthan_or_equal) || accept(greater_than) || accept(less_than) || accept(equal_equal)){
        cond=create_binary_node(prev_tok.type);
        cond->children[0]=temp;
        if(accept(identifier) || accept(const_num)){
            temp=create_ast(prev_tok);
            cond->children[1]=temp;
        }
        else{
        error("Expecting variable or number");
        }
    }
    else{
    error("Expecting compare operator");
    }
}else{
error("Expecting variable or number");
}
return cond;
}

struct AST_NODE *if_statement() {
while(accept(next_line));
///First child is condition second is true case third is false case
struct AST_NODE *temp,*ifcond;
if(accept(_if)){
    expect(open_brac,"Expecting ( after if");
    ifcond=create_if_node();
    ifcond->children[0]=condition();
    expect(close_brac,"Expecting ) after conditional statement");
    _expect(open_fbrac,"Expecting { after if statement");
    ifcond->children[1]=statements();///<----------------------------------------------------Changes needed
    _expect(close_fbrac,"Not found:} of if statement");
    ifcond->children[2]=NULL;
    while(accept(next_line));
    if(accept(_else)){
            _expect(open_fbrac,"Not found:{ of else statement");
            ifcond->children[2]=statements();
            _expect(close_fbrac,"Not found:} of else statement");
    }

}else{
error("Unexpected token has appeared");
}
return ifcond;
}


struct AST_NODE *while_statement() {
while(accept(next_line));
struct AST_NODE *while_node=0;
if(accept(_while)){
    while_node=create_whie_node();
    expect(open_brac,"Expecting ( after while");
    while_node->children[0]=condition();
    expect(close_brac,"Expecting ) after conditional statement");
    _expect(open_fbrac,"Expecting { after while statement");
    while_node->children[1]=statements();
    _expect(close_fbrac,"Not found:} end of while not found");

}else{
error("Unexpected token has appeared");
}
return while_node;
}

struct AST_NODE *assingment_statement()
{
///Left child is variable to be assigned and right is equation or value
while(accept(next_line));
struct AST_NODE *assign,*temp;
if(accept(identifier))
    {
    temp=create_ast(prev_tok);
    expect(_equal,"Expecting = after variable");
    assign=create_binary_node(_equal);
    if(curr_tok.type==_string){
        assign->children[0]=temp;
        assign->children[1]=parse_string();
    }
    else{
    assign->children[0]=temp;
    assign->children[1]=expression();
    }
}

else{
error("Invalid statement");
}
return assign;
}
struct AST_NODE *parse_string(){
struct AST_NODE *s;
if(accept(_string)){

    s=create_ast(prev_tok);
    return s;
}
return 0;
}

struct AST_NODE *display_statement(){
/*Root type is display
  Children
*/

struct AST_NODE *x,*temp,*tail;
x=create_ast(curr_tok);
tail=x;
next_token();
while(curr_tok.type!=next_line && curr_tok.type!=EOP){
if(!(accept(_string) || accept(identifier)))
error("Expecting string or identifier in display statement");
temp=create_ast(prev_tok);
tail->children=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
tail->children[0]=temp;
tail=temp;
}
tail->children=(struct AST_NODE *)malloc(sizeof(struct AST_NODE));
tail->children[0]=0;
return x;
}


///-------------------------------------------------------------------------------------------------------////
void add_node_to_next(struct AST_NODE **root,struct AST_NODE *t,struct AST_NODE **end)///Statement helper function
{
///Comments needed
if(*root==0){
    *root=t;
    *end=t;
    return;
}
(*end)->next=t;
if(t!=0)
*end=t;
}

struct AST_NODE *statements()
{
    struct AST_NODE *root=0,*temp,*end;
    while(accept(next_line));
    if(curr_tok.type==identifier){
        temp=assingment_statement();
        add_node_to_next(&root,temp,&end);
        temp=statements();
        add_node_to_next(&root,temp,&end);
    }
    else if(curr_tok.type==_if){
        temp=if_statement();
        add_node_to_next(&root,temp,&end);
        temp=statements();
        add_node_to_next(&root,temp,&end);
    }
    else if(curr_tok.type==display){
        temp=display_statement();
        add_node_to_next(&root,temp,&end);
        temp=statements();
        add_node_to_next(&root,temp,&end);

    }
    else if(curr_tok.type==_while) {
        temp=while_statement();
        add_node_to_next(&root,temp,&end);
        temp=statements();
        add_node_to_next(&root,temp,&end);

    }
    else if(curr_tok.type==EOP || curr_tok.type==close_fbrac || curr_tok.type==next_line){
    return 0;
    }
    else{
    error("Invalid Statement");
    }
return root;
}

