#ifndef PARSING_FUN_H
#define PARSING_FUN_H

#include <stdlib.h>

typedef struct s_cnode {
    char *command;
    char **args;
    struct s_cnode *next;
} t_cnode;

typedef struct s_clist {
    t_cnode *command_chain;
    struct s_clist *next;
} t_clist;

t_cnode *new_node();
t_clist *new_list();
char	**ft_split_space(char const *s);
void	str_arr_copy(char **dest, char **src);
int		str_arr_length(char **arr);
t_cnode	*add_back_command(t_cnode *node, t_cnode *command);
t_clist	*add_back_list(t_clist *node, t_clist *list);
char	**str_arr_resize(char **arr, int new_size);

#endif
