#ifndef VAR
#define VAR
#include "datastructure.h"
struct Variable
{
    enum TokenType var_type;
    void *value;
};
struct Variable *create_variable(enum TokenType var_type,void *value);

struct Variable *get_variable(char *name);
#endif // VAR
