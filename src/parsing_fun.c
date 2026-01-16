#include "parsing_fun.h"
#include <stdio.h>

void	parse_input(t_clist *list, char **input)
{
	int		i;
	int		j;
	t_clist	*new_list_node;
	t_cnode	*new_cmd_node;
	char	*stripped_arg;
	int		x;

	i = 0;
	j = 0;
	new_cmd_node = new_node();
	list->command_chain = new_cmd_node;
    new_list_node = list;
	while (input[i])
	{
		if (ft_strcmp(input[i], "|") == 0)
		{
			new_cmd_node = new_node();
			add_back_command(new_cmd_node, new_list_node->command_chain);
			j = 0;
			++i;
			continue ;
		}
		if (ft_strcmp(input[i], ";") == 0)
		{
			new_list_node = new_list();
			add_back_list(new_list_node, list);
			new_cmd_node = new_node();
			new_list_node->command_chain = new_cmd_node;
			j = 0;
			++i;
			continue ;
		}
        // shitty code i know
		if (input[i][ft_strlen(input[i]) - 1] == ';')
		{
			stripped_arg = malloc(ft_strlen(input[i]));
			x = 0;
			while (x < ft_strlen(input[i]) - 1)
			{
				stripped_arg[x] = input[i][x];
				x++;
			}
			stripped_arg[x] = '\0';
			
			// -----
			if (new_cmd_node->command == NULL)
			{
				new_cmd_node->command = ft_strdup(stripped_arg);
			}
			else
			{
				new_cmd_node->args = str_arr_resize(new_cmd_node->args, 2 + j);
				new_cmd_node->args[j] = ft_strdup(stripped_arg);
				new_cmd_node->args[j + 1] = NULL;
			}
			new_list_node = new_list();
			add_back_list(new_list_node, list);
			new_cmd_node = new_node();
			new_list_node->command_chain = new_cmd_node;
			j = 0;
			++i;
			continue ;
			// -----
		}
		if (new_cmd_node->command == NULL)
		{
			new_cmd_node->command = ft_strdup(input[i]);
			++i;
			continue ;
		}
		new_cmd_node->args = str_arr_resize(new_cmd_node->args, 2 + j);
		new_cmd_node->args[j] = ft_strdup(input[i]);
		new_cmd_node->args[j + 1] = NULL;
		++i;
		++j;
	}
}

void	print_parsed(t_clist *list)
{
	int		i;
	int		j;
	t_clist	*node;
	t_cnode	*chain;

	i = 0;
	j = 0;
	node = list;
	while (node)
	{
		printf("---chain %d\n", i);
		chain = node->command_chain;
		while (chain)
		{
			j = 0;
			printf("--command: %s\n-args:\n", chain->command);
			while (chain->args[j])
			{
				printf("%s\n", chain->args[j]);
				j++;
			}
			chain = chain->next;
		}
		node = node->next;
		++i;
	}
}

int	main(int argc, char **argv)
{
	t_clist *list;
	char **input;

	if (argc != 2)
		return (0);
	list = new_list();
	input = split_space(argv[1]);
	parse_input(list, input);
	print_parsed(list);
}