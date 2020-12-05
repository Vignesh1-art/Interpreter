#include "datastructure.h"
#include "variable.h"
#include "hash.h"

void init_variable()
{
    init_hashtable();
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
