#include "datastructure.h"
#include "variable.h"
#include "hash.h"

void init_variable()
{
    init_hashtable();
}

void var_error(char *msg)
{
printf("Variable Resolver : %s",msg);
exit(0);
}

struct Variable *create_variable(enum TokenType var_type,void *value)
{
struct Variable *x=(struct Variable *)malloc(sizeof(struct Variable));
x->value=value;
x->var_type=var_type;
return x;
}

void define_variable(char *name,struct Variable *var)
{
    add_to_hashtable(name,var);
}

struct Variable *get_variable(char *name)
{
return get_hash_value(name);
}

short int isdefined(char *name)
{
 struct Variable *x=get_hash_value(name);
 if(x==0)
    return 0;
 return 1;
}

int get_int(char *name)
{
    struct Variable *x=get_hash_value(name);

    if(x==0 || x->var_type!=_int)
    {
        error("Variable error: Not defined as int");
    }
    int *a=x->value;
    return *a;
}

int *get_intptr(char *name)
{
    struct Variable *x=get_hash_value(name);

    if(x==0 || x->var_type!=_int)
    {
        error("Variable error: Not defined as int");
    }
    return x->value;
}


