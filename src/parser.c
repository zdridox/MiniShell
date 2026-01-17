#include "parser.h"

void parse_tokens(t_cmd_node *cmd_head, char **tokens) {
    t_cmd_node *curr_node;

    
}

int main(int argc, char **argv)
{
    char **tokens;
    t_cmd_node *head;

    if (argc != 2)
        return (0);
    tokens = tokenizer(argv[1]);
    head = malloc(sizeof(t_cmd_node));

    return (0);
}
