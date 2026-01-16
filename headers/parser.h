#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>

typedef enum s_flag_type
{
    OVERWRITE,
    APPEND,
} t_flag_type;

typedef struct s_flag
{
    t_flag_type flag;
    char **flag_argv;
} t_flag;

typedef struct s_cmd_node
{
    t_flag *flags;
    char **argv;
    struct s_cmd_node *next;
} t_cmd_node;

#endif