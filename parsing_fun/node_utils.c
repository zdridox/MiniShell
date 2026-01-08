#include "parsing_fun.h"

t_cnode	*add_back_command(t_cnode *node, t_cnode *command)
{
	t_cnode	*node_p;

	node_p = command;
	while (node_p->next)
		node_p = node_p->next;
    node_p->next = node;
}

t_cnode	*new_node()
{
	t_cnode	*node;

	node = malloc(sizeof(t_cnode));
	node->command = NULL;
	node->args = malloc(1 * sizeof(char *));
    node->args[0] = NULL;
	node->next = NULL;
	return (node);
}

t_clist	*add_back_list(t_clist *node, t_clist *list)
{
	t_clist	*node_p;

	node_p = list;
	while (node_p->next)
		node_p = node_p->next;
    node_p->next = node;
}

t_clist	*new_list(void)
{
	t_clist *list;

	list = malloc(sizeof(t_clist));
	list->next = NULL;
	return (list);
}