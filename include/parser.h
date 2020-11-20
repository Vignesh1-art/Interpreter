#ifndef parser
#define parser
void init_parser(char *);

struct AST_NODE *parse_string();
struct AST_NODE *statements();
struct AST_NODE *assingment_statement();

#endif // parser
