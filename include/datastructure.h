#ifndef DS
#define DS
#define maxsize 20
//Here all the Data structure used defined here
enum TokenType{_if,_else,_while,identifier,var,const_num,open_fbrac,close_fbrac,
open_brac,close_brac,//9
_add,_sub,_div,_mult,no_op,_equal,
cond,equal_equal,less_than,greater_than,lessthan_or_equal,greaterthan_or_equal,next_line,EOP};

struct Token{
int line;
enum TokenType type;
char *lexeme;
};

struct AST_NODE{
    enum TokenType type;
    void *content;
    struct AST_NODE **children; //Array of children
    struct AST_NODE *next;//Pointer to next sibling
};

struct token_stack{
struct Token node[maxsize];
int top;
}st;

void init_tok_stack();
int is_stack_empty();
struct Token top_stack();
struct Token pop_from_token_stack();
struct token_queue{
int f,r;
struct Token nodeq[maxsize];
}q;
void init_queue();

int is_queue_empty();
void print_q_content();
void insert_to_Tokq(struct Token );

#endif // DS
