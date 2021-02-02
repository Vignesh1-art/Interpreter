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

int get_int(char *);///Return variable

int *get_intptr(char *);///Returns pointer to variable
#endif // VAR
