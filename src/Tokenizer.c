#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "datastructure.h"
char *inputbuffer;
char buf[50];
int index=0;
int line=0;
int buf_index=0;
void add_to_buf(char c){
buf[buf_index]=c;
buf_index++;
buf[buf_index]=0;//add end
}
void resetbuf(){
buf[0]=0;
buf_index=0;
}
void init_tokenizer(char *input){
index=0;
buf_index=0;
inputbuffer=input;
line=0;
}

int isNum(char *x){
for(int i=0;x[i]!=0;i++){
    if(!isdigit(x[i]))
        return 0;
}
return 1;
}

enum TokenType get_tok_type(char *s){
if(strcmp(s,"if")==0)
    return _if;
if(strcmp(s,"while")==0)
    return _while;
if(strcmp(s,"display")==0)
    return display;
return identifier;
}



struct Token get_token(){
    struct Token tok;
    tok.lexeme=0;
while(inputbuffer[index]==' ')
    index++;
while(isalnum(inputbuffer[index])){
    add_to_buf(inputbuffer[index]);
    index++;
}
int l=strlen(buf);
if(l>0){
    tok.lexeme=malloc(l*sizeof(char));
    strcpy(tok.lexeme,buf);
    if(isNum(tok.lexeme))
        tok.type=const_num;
    else
        tok.type=get_tok_type(tok.lexeme);
    resetbuf();
    tok.line=line;
    return tok;///<---------------------------------------RETURN
}

switch(inputbuffer[index]){
case '{':tok.type=open_fbrac;
index++;
break;
case '}':tok.type=close_fbrac;
index++;
break;
case '(':tok.type=open_brac;
index++;
break;
case ')':tok.type=close_brac;
index++;
break;
case '+':tok.type=_add;
index++;
break;
case '-':tok.type=_sub;
index++;
break;
case '*':tok.type=_mult;
index++;
break;
case '/':tok.type=_div;
index++;
break;
case '%':tok.type=mod;
index++;
break;
case '\n':tok.type=next_line;
line++;
index++;
break;
case '"':
    index++;
    while(inputbuffer[index]!='"'){
        add_to_buf(inputbuffer[index]);
        index++;
    }
    int l=strlen(buf);
    if(l>0){
    tok.lexeme=malloc(l*sizeof(char));
    strcpy(tok.lexeme,buf);
    }
    tok.type=_string;
    index++;
break;
case 0:tok.type=EOP;///END OF PROGRAM don't increment index
break;
///Checking possible size 2 tokens
case '=':

    if(inputbuffer[index+1]=='='){
        index+=2;
        tok.type=equal_equal;
    }else{
    index++;
    tok.type=_equal;
    }
break;

case '<':
    if(inputbuffer[index+1]=='='){
        index+=2;
        tok.type=lessthan_or_equal;
    }else{
    index++;
    tok.type=less_than;
    }
break;

case '>':
    if(inputbuffer[index+1]=='='){
        index+=2;
        tok.type=greaterthan_or_equal;
    }else{
    index++;
    tok.type=greater_than;
    }
break;
default:printf("Tokenizer:Stray appeared in %c index:%d\n",inputbuffer[index],index);
exit(0);
}
resetbuf();///<---------------------------------------RETURN
tok.line=line;
return tok;
}



