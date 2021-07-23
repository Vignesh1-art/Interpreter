#include "datastructure.h"
#include "variable.h"
#include "ast.h"

///Defination of internal functions
struct interpreter_stack{
struct AST_NODE *items[100];
int top;
}intr_st;


void init_intr_stack(){
intr_st.top=-1;
}

void intr_push(struct AST_NODE *item){
intr_st.top++;
intr_st.items[intr_st.top]=item;
}

struct AST_NODE *intr_pop()
{
    if(intr_st.top==-1)
        return 0;
    intr_st.top--;
  return intr_st.items[intr_st.top+1];
}

void init_interpreter()
{
    init_variable();
}

int eval_tree(struct AST_NODE *root){///Internal function
    int *a;
if(root==0)
    return 0;
if(root->children[0]==0 && root->children[1]==0)
{
    if(root->type==identifier)
    return get_int(root->content);
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
case mod:return (l_val%r_val);
default:error("Parser supplied invalid expression");
}

}


short int eval_condition(struct AST_NODE *root){
    int *a,*b;

if(root->children[0]->type==identifier)
    a=get_intptr(root->children[0]->content);
else
    a=root->children[0]->content;

if(root->children[1]->type==identifier)
    b=get_intptr(root->children[1]->content);
else
    b=root->children[1]->content;

switch(root->type){
case equal_equal:
    return (*a==*b);
case lessthan_or_equal:
    return (*a<=*b);
case greaterthan_or_equal:
    return (*a>=*b);
case greater_than:
    return (*a>b);
case less_than:
    return (*a<*b);
}
}


void interpret(struct AST_NODE *root)
{
    int value;
    int *tmp_int_pointer;
    short int flag;
    char *c;
    init_intr_stack();
    struct AST_NODE *curr_node=root,*temp;
  for(;;)///Interpreter main loop
    {
    if(curr_node==0)
    {
        curr_node=intr_pop();
    }
    if(curr_node==0)///Stop if no next node found
        break;

    switch(curr_node->type){


    case _equal:
        if(curr_node->children[1]->type==_string){
            struct Variable *st=create_variable(_string,curr_node->children[1]->content);
            define_variable(curr_node->children[0]->content,st);
            curr_node=curr_node->next;
            break;
        }
        value=eval_tree(curr_node->children[1]);
        tmp_int_pointer=(int)malloc(sizeof(int));
        *tmp_int_pointer=value;
        struct Variable *v=create_variable(_int,tmp_int_pointer);
        define_variable(curr_node->children[0]->content,v);
        curr_node=curr_node->next;
        break;


    case _if:

        flag=eval_condition(curr_node->children[0]);
        if(flag==1){
            intr_push(curr_node->next);
            curr_node=curr_node->children[1];
        }
        else if(curr_node->children[2]){
            intr_push(curr_node->next);
            curr_node=curr_node->children[2];
        }else{
            curr_node=curr_node->next;
        }
        break;


    case display:

        temp=curr_node->children[0];
        while(temp!=0){
            if(temp->type==identifier){
            struct Variable *var=get_variable(temp->content);
                if(var!=0) {
                        if(var->var_type==_int){
                                tmp_int_pointer=var->value;
                                printf("%d",*tmp_int_pointer);
                        }
                        else {
                            c=var->value;
                            printf("%s",c);
                        }

                }
            } else if(temp->type==_string) {
            c=temp->content;
            if(strcmp(c,"\\n")==0) {
                printf("\n");
            }else {
                printf("%s",c);
            }
            }
           temp=temp->children[0];
            }
        curr_node=curr_node->next;
        break;

    case _while:
        flag=eval_condition(curr_node->children[0]);
        if(flag==1) {
        /*In case of while (unlike it is done in if) we push curr_node to stack as we want
        control to come here to check condition and execute again if true*/
        intr_push(curr_node);
        curr_node=curr_node->children[1];
        }else {
        curr_node=curr_node->next;
        }
    break;

    default:printf("Interpreter could not handle statement %d",curr_node->type);
    exit(0);

    }


  }///end interpreter loop
}


