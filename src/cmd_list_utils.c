#include "../headers/parser.h"

void cmd_add_back(t_cmd_node *head, t_cmd_node *node) {
    t_cmd_node *p;

    p = head;
    while (p->next)
        p = p->next;
    p->next = node;
    
}