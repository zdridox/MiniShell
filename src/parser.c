#include "../headers/parser.h"
// #include "../headers/minishell.h"

t_cmd_node *parse_tokens(char **tokens)
{
    t_cmd_node *parsed;
    t_cmd_node *curr;
    t_flag_node *flag;

    curr = NULL;
    while (*tokens)
    {
        if (curr == NULL)
        {
            curr = malloc(sizeof(t_cmd_node *));
            curr->flags = NULL;
        }
        if (!ft_strncmp(*tokens, "|", 1))
        {
            cmd_add_back(parsed, curr);
            curr = malloc(sizeof(t_cmd_node *));
            curr->flags = NULL;
        }
        else if (!ft_strncmp(*tokens, ">", 1) || !ft_strncmp(*tokens, ">>", 2) || !ft_strncmp(*tokens, "<", 1) || !ft_strncmp(*tokens, "<<", 2))
        {
            flag = malloc(sizeof(t_flag_node *));
            flag_add_back(curr->flags, flag);
            if (!ft_strncmp(*tokens, ">", 1))
                flag->flag = OVERWRITE;
            if (!ft_strncmp(*tokens, ">>", 2))
                flag->flag = APPEND;
            if (!ft_strncmp(*tokens, "<", 1))
                flag->flag = READ_FROM_FILE;
            if (!ft_strncmp(*tokens, "<<", 2))
                flag->flag = HEREDOC;
        }
        else
        {
            if (curr->flags == NULL)
            {
                curr->argv = resize_str_arr(curr->argv, str_arr_len(curr->argv) + 1);
                curr->argv[str_arr_len(curr->argv)] = ft_strdup(*tokens);
            }
            else
            {
                flag->flag_argv = resize_str_arr(flag->flag_argv, str_arr_len(flag->flag_argv) + 1);
                flag->flag_argv[str_arr_len(flag->flag_argv)] = ft_strdup(*tokens);
            }
        }
        ++tokens;
    }
}

void print_parsed(t_cmd_node *parsed)
{
    t_cmd_node *cp;
    t_flag_node *fp;
    char **sap;

    cp = parsed;
    while (cp)
    {
        ft_printf("---COMMAND---");
        sap = cp->argv;
        while (sap)
        {
            ft_printf("%s\n", sap);
            ++sap;
        }
        fp = cp->flags;
        while (fp)
        {
            ft_printf("---FLAG---");
            switch (fp->flag)
            {
            case OVERWRITE:
                ft_printf("OVERWRITE");
                break;
            case APPEND:
                ft_printf("APPEND");
                break;
            case READ_FROM_FILE:
                ft_printf("READ_FROM_FILE");
                break;
            case HEREDOC:
                ft_printf("HEREDOC");
                break;

            default:
                break;
            }
            sap = fp->flag_argv;
            while (sap)
            {
                ft_printf("%s\n", sap);
                ++sap;
            }
            fp = fp->next;
        }

        cp = cp->next;
    }
}

int main(int argc, char **argv)
{
    char **tokens;
    t_cmd_node *parsed;

    if (argc != 2)
        return (0);
    tokens = tokenizer(argv[1]);
    parsed = parse_tokens(tokens);
    print_parsed(parsed);
    return (0);
}
