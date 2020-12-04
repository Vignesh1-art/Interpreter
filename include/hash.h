#ifndef HASH
#define HASH
#include "variable.h"
struct Variable_pointer
{
    char *name;
    struct Variable *ptr;
    struct Variable_pointer *next;
};

struct Variable_pointer *get_var_pointer();
void add_to_hashtable(char *key,struct Variable * value);
void add_to_hashtable(char *key,struct Variable * value);
void define_variable(char *name,struct Variable *var);
#endif // HASH
