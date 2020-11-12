#ifndef EXP
#define EXP
struct node_stack{
int top;
struct AST_NODE *items[20];
}node_stack;


void init_node_stack();

void push_to_node_stack(struct AST_NODE *);

struct AST_NODE *pop_from_node_stack();

struct AST_NODE *create_exp_tree_from_q();

void traverse_tree(struct AST_NODE *);

int eval_tree(struct AST_NODE *);
#endif // EXP
