#include "../headers/parser.h"

void cmd_add_back(t_cmd_node *head, t_cmd_node *node)
{
    t_cmd_node *p;

    p = head;
    while (p->next)
        p = p->next;
    p->next = node;
}

void flag_add_back(t_flag_node *head, t_flag_node *node)
{
    t_flag_node *p;

    p = head;
    while (p->next)
        p = p->next;
    p->next = node;
}
