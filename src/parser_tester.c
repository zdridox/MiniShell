#include "parser_new.h"
#include <stdio.h>

void	print_word_parts(t_word_part *word_parts)
{
	char	*word_part_type_str[] = {
		"PLAIN",
		"SINGLE_QUOTED",
		"DOUBLE_QUOTED"
	};
	int	part_num;

	part_num = 1;
	while (word_parts)
	{
		if (word_parts->type == PLAIN)
			printf("  Part %d: %s (PLAIN)\n", part_num, word_parts->value);
		else if (word_parts->type == SINGLE_QUOTED)
			printf("  Part %d: '%s' (SINGLE_QUOTED)\n", part_num, word_parts->value);
		else if (word_parts->type == DOUBLE_QUOTED)
			printf("  Part %d: \"%s\" (DOUBLE_QUOTED)\n", part_num, word_parts->value);
		word_parts = word_parts->next;
	}
}

void	print_word_parts_inline(t_word_part *word_parts)
{
	while (word_parts)
	{
		if (word_parts->type == PLAIN)
			printf("%s", word_parts->value);
		if (word_parts->type == SINGLE_QUOTED)
			printf("'%s'", word_parts->value);
		if (word_parts->type == DOUBLE_QUOTED)
			printf("\"%s\"", word_parts->value);
		word_parts = word_parts->next;
	}
}

void	print_tokens(t_token *tokens)
{
	char	*token_type_str[] = {
		"WORD",
		"PIPE",
		"REDIRECT_IN",
		"REDIRECT_OUT",
		"APPEND",
		"HEREDOC",
		"AND",
		"OR",
		"LEFT_PARENTHESIS",
		"RIGHT_PARENTHESIS",
		"ERROR",
		"END"
	};
	int	token_num = 1;

	while (tokens)
	{
		printf("Token %d: %s\n", token_num, token_type_str[tokens->type]);
		if (tokens->word_parts)
			print_word_parts(tokens->word_parts);
		tokens = tokens->next;
	}
}

void	print_ast_type(t_node_type type)
{
	char	*ast_type_str[] = {
		"COMMAND",
		"PIPE",
		"AND",
		"OR",
	};
	printf("%s", ast_type_str[type]);
}

void	print_ast_indent(int indent, bool is_left, bool is_first_left)
{
	int	i;

	i = 0;
	while (i < indent)
	{
		if (i == 0 && is_first_left && indent > 1)
			printf("    ");
		else if (i == 0 && indent > 1 && !is_first_left)
			printf("│   ");
		if	(i == indent - 1)
		{
			if (is_left)
				printf("└── ");
			else
				printf("├── ");
		}
		if (i < indent - 1 && i != 0)
			printf("│   ");
		i++;
	}
}

void	print_ast_word_parts(t_word_part *word_parts, int indent, bool is_first_left)
{
	while (word_parts)
	{
		if (word_parts->type == PLAIN)
			printf("%s", word_parts->value);
		else if (word_parts->type == SINGLE_QUOTED)
			printf("'%s'", word_parts->value);
		else if (word_parts->type == DOUBLE_QUOTED)
			printf("\"%s\"", word_parts->value);
		word_parts = word_parts->next;
	}
}

void	print_ast_words(t_word *words, int indent, bool is_first_left)
{
	while (words)
	{
		print_ast_word_parts(words->word_parts, indent, is_first_left);
		printf(" ");
		words = words->next;
	}
}

void	print_ast_redirects(t_redirect_node *redirects, int indent, bool is_first_left)
{
	bool	is_last_redirect;

	is_last_redirect = false;
	print_ast_indent(indent, true, is_first_left);
	printf("redirects: ");
	if (!redirects)
	{
		printf("(none)");
		return ;
	}
	while (redirects)
	{
		char	*redirect_type_str[] = {
			"<",
			">",
			">>",
			"<<"
		};
		if (!redirects->next)
			is_last_redirect = true;
		printf("\'%s\' : \'", redirect_type_str[redirects->type]);
		print_ast_word_parts(redirects->target->word_parts, indent, is_first_left);
		printf("\'");
		if (!is_last_redirect)
			printf(", ");
		redirects = redirects->next;
	}
}

void	print_ast_command(t_command *command, int indent, bool is_left, bool is_first_left)
{
	print_ast_indent(indent + 1, false, is_first_left);
	printf("args: ");
	print_ast_words(command->words, indent + 1, is_first_left);
	printf("\n");
	print_ast_redirects(command->redirects, indent + 1, is_first_left);
	printf("\n");
}

void	print_node(t_ast_node *node, int indent, bool is_left, bool is_first_left)
{
	if (is_left && indent == 1)
		is_first_left = true;
	if (!node)
	{
		printf("(null)\n");
		return ;
	}
	print_ast_indent(indent, is_left, is_first_left);
	print_ast_type(node->type);
	printf("\n");
	if (node->command)
		print_ast_command(node->command, indent + 1, is_left, is_first_left);
	if (node->right)
		print_node(node->right, indent + 1, false, is_first_left);
	if (node->left)
		print_node(node->left, indent + 1, true, is_first_left);
}

void	print_ast(t_ast_node *ast)
{
	print_node(ast, 0, false, false);
}

void	run_parser_tests(void)
{
	char		*inputs[] = {
		"grep 'pattern' < input.txt | sort | grep 'another pattern' > output.txt",
		"grep 'pattern' && echo 'found' || echo 'not found'",
		"grep 'pattern' && (echo 'found' || echo 'not found')",
		"grep 'pattern' || (echo 'found' && echo 'not found')",
		"ls -l /home/user && (cd /home/user && echo 'done') || echo 'failed'",
		"echo 'This is a test' > test.txt && cat test.txt || echo 'Failed to create file'",
		"sh -c 'echo \"Nested quotes\" && echo \"Another command\"' && echo 'Done' || echo 'Failed'",
		"ls -l /home/user | grep 'pattern' && echo 'Pattern found' || echo 'Pattern not found'",
		"cat << EOF\nThis is a heredoc test.\nIt should be parsed correctly.\nEOF",
		NULL
	};
	int			i;
	t_token		*tokens;
	t_ast_node	*ast;

	i = 0;
	while (inputs[i])
	{
		printf("Input: %s\n\n", inputs[i]);
		tokens = tokenize_input(inputs[i]);
		print_tokens(tokens);
		printf("\n-----------------------------\n\n");
		ast = parse_tokens(tokens);
		printf("AST:\n\n");
		print_ast(ast);
		printf("\n-----------------------------\n\n");
		i++;
	}
}

int	main(void)
{
	run_parser_tests();
	return (0);
}
