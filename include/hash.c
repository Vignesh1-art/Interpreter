#include<stdio.h>
#include "hash.h"
#include "variable.h"
#define max 50

struct Variable_pointer **table;

struct Variable_pointer *get_var_pointer(){
    struct Variable_pointer *x=(struct Variable_pointer *)malloc(sizeof(struct Variable_pointer));
    x->next=0;
return x;
}

void init_hashtable()
{
    table=(struct Variable_pointer **)calloc(max,sizeof(struct Variable_pointer *));
}

void add_to_hashtable(char *key,struct Variable *value)
{
    int k=0;

    for(int i=0;key[i]!=0;i++)
        k+=key[i];
    k=k%max;
    struct Variable_pointer *temp=table[k];
    while(temp!=0)
    {
        if(temp->name==key)
        {
            temp->ptr=value;
            return;
        }
        else if(temp->next==0)
        break;
        temp=temp->next;
    }
        if(temp==0)
        {
            table[k]=get_var_pointer();
            table[k]->name=key;
            table[k]->ptr=value;
        }
        else
        {
            temp->next=get_var_pointer();
            (temp->next)->ptr=value;
            (temp->next)->name=key;
        }

}

struct Variable * get_hash_value(char *key)
{
    int k=0;
    for(int i=0;key[i]!=0;i++)
        k+=key[i];
    k=k%max;
    struct Variable_pointer *temp=table[k];
    while(temp!=0)
    {
        if(temp->name==key)
            return temp->ptr;
        else
            temp=temp->next;
    }
    return -1;
}


