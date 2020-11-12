#include<stdio.h>
#include "datastructure.h"
///---STACK---

void init_tok_stack(){
    st.top=-1;
}

int is_stack_empty(){
if(st.top==-1)
    return 1;
return 0;
}

struct Token top_stack(){
return st.node[st.top];
}

void push_to_token_stack(struct Token x){
if(st.top>maxsize){
printf("Parser stack error:Overflow\n");
exit(0);
}
st.top++;
st.node[st.top]=x;
}

struct Token pop_from_token_stack(){
if(st.top<0){
printf("Token stack error:Underflow\n");
exit(0);
}
st.top--;
//printf("Popping %d\n",st.node[st.top+1].type);
return st.node[st.top+1];
}
///---QUEUE---
void init_queue(){
q.f=-1;
q.r=-1;
}
int is_queue_empty(){
if(q.f==-1)
    return 1;
return 0;
}
void print_q_content(){
for(int i=0;i<=q.f;i++)
    printf("%s---%d\n",q.nodeq[i].lexeme,q.nodeq[i].type);

}
void insert_to_Tokq(struct Token item)
{
   q.f++;
   q.nodeq[q.f]=item;

}




