#include "../headers/parser.h"
// #include "../headers/minishell.h"

// No, that command is perfectly valid in a standard shell like bash or zsh. This is a key concept for building your minishell and highlights the

// issue with your current parser.

// Here is how a standard shell interprets echo "Asdasd" > file something here:

// The shell scans the command line for special characters. It finds the redirection > file.
// It processes this redirection first. It opens the file named file for writing, preparing it to receive the command's output.
// The redirection part (> file) is then removed from the command line.
// The shell is left with echo "Asdasd" something here.
// It then executes the echo command, passing it "Asdasd", something, and here as three separate arguments.
// So, the final result is:

// Command: echo
// Arguments: "Asdasd", something, here
// Output: The text Asdasd something here is written into the file named file.

t_cmd_node *parse_tokens(char **tokens)
{
    t_cmd_node *parsed;
    t_cmd_node *curr;
    t_flag_node *flag;

    curr = NULL;
    parsed = NULL;
    while (*tokens)
    {
        if (curr == NULL)
        {
            curr = malloc(sizeof(t_cmd_node));
            curr->argv = NULL;
            curr->flags = NULL;
            curr->next = NULL;
        }
        if (!ft_strncmp(*tokens, "|", 1))
        {
            if (parsed)
            {
                cmd_add_back(parsed, curr);
            }
            else
            {
                parsed = curr;
            }
            curr = malloc(sizeof(t_cmd_node));
            curr->argv = NULL;
            curr->flags = NULL;
            curr->next = NULL;
        }
        else if (!ft_strncmp(*tokens, ">", 1) || !ft_strncmp(*tokens, ">>", 2) || !ft_strncmp(*tokens, "<", 1) || !ft_strncmp(*tokens, "<<", 2))
        {
            flag = malloc(sizeof(t_flag_node));
            flag->flag_arg = NULL;
            flag->next = NULL;
            if (curr->flags)
            {
                flag_add_back(curr->flags, flag);
            }
            else
            {
                curr->flags = flag;
            }
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
            if (!(flag && !flag->flag_arg))
            {
                curr->argv = resize_str_arr(curr->argv, str_arr_len(curr->argv) + 1);
                curr->argv[str_arr_len(curr->argv)] = ft_strdup(*tokens);
            }
            else
            {
                flag->flag_arg = ft_strdup(*tokens);
            }
        }
        ++tokens;
    }

    if (parsed)
    {
        cmd_add_back(parsed, curr);
    }
    else
    {
        parsed = curr;
    }
    return (parsed);
}

void print_parsed(t_cmd_node *parsed)
{
    t_cmd_node *cp;
    t_flag_node *fp;

    cp = parsed;
    while (cp)
    {
        ft_printf("---COMMAND---\n");
        print_str_arr(cp->argv);
        fp = cp->flags;
        while (fp)
        {
            ft_printf("---FLAG---\n");
            switch (fp->flag)
            {
            case OVERWRITE:
                ft_printf("-OVERWRITE-\n");
                break;
            case APPEND:
                ft_printf("-APPEND-\n");
                break;
            case READ_FROM_FILE:
                ft_printf("-READ_FROM_FILE-\n");
                break;
            case HEREDOC:
                ft_printf("-HEREDOC-\n");
                break;

            default:
                break;
            }
            ft_printf("%s\n", fp->flag_arg);
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
