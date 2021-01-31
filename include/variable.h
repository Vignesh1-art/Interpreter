#ifndef VAR
#define VAR
#include "datastructure.h"
struct Variable
{
    enum TokenType var_type;
    void *value;
};
struct Variable *create_variable(enum TokenType,void *);

struct Variable *get_variable(char *name);

int get_int(char *);
#endif // VAR
