#include "../headers/parser.h"
#include "../headers/minishell.h"

static int	is_space(char a)
{
	return (a == 9 || a == 10 || a == 11 || a == 12 || a == 13 || a == 32);
}

static int	token_counter(const char *s)
{
	const char	*p;
	int			word_count;
	int			in_word;
	char		brace_flag;

	brace_flag = '\0';
	p = s;
	in_word = 0;
	word_count = 0;
	while (*p != '\0')
	{
		if (*p == '"' || *p == '\'')
		{
			if (brace_flag == '\0')
			{
				brace_flag = *p;
			}
			else
			{
				if (brace_flag == *p)
					brace_flag = '\0';
			}
		}
		if (!is_space(*p))
			in_word = 1;
		if (is_space(*p) && in_word == 1 && brace_flag == '\0')
		{
			word_count++;
			in_word = 0;
		}
		p++;
	}
	if (in_word == 1)
		word_count++;
	return (word_count);
}

char	**tokenizer(char *input)
{
	char	*p;
	char	*trimmed;
	int		i;
	int		j;
	int		brace_flag;
	char	**tokens;
	int in_word;
	static char trim_set[] = {9, 10, 11, 12, 13, 32};

	i = 0;
	j = 0;
	brace_flag = 0;
	in_word = 0;
	trimmed = ft_strtrim(input, trim_set);
	p = trimmed;
	tokens = malloc(sizeof(char *) * (token_counter(input) + 1));
	while (*p)
	{
		if (*p == '"' || *p == '\'')
		{
			if (brace_flag == '\0')
				brace_flag = *p;
			else
			{
				if (brace_flag == *p)
					brace_flag = '\0';
			}
		}
		if(!is_space(*p))
			in_word = 1;
		if ((is_space(*p) || *(p + 1) == '\0') && brace_flag == '\0' && in_word == 1)
		{
			tokens[j] = malloc(i + 1 + (*(p + 1) == '\0'));
			ft_memcpy(tokens[j], p - i, i + (*(p + 1) == '\0'));
			tokens[j][i + (*(p + 1) == '\0')] = '\0';
			j++;
			i = 0;
			in_word = 0;
		}
		else if(!is_space(*p) || brace_flag != '\0')
			i++;
		p++;
	}
	tokens[j] = NULL;
	free(trimmed);
	return (tokens);
}

// int	main(void)
// {
// 	char *str = readline("test jebanego tokenizera: ");
// 	//char **tokens = tokenizer("echo \"srakaw  ilkolaka\"");
// 	char **tokens = tokenizer(str);

// 	for (int i = 0; tokens[i]; i++) {
// 		ft_printf(".%s.\n", tokens[i]);
// 		free(tokens[i]);
// 	}
// 	free(tokens);
// 	return (0);
// }
