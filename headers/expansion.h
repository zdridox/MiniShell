#ifndef EXPANSION_H
#define EXPANSION_H

#define INITIAL_STRING_VECTOR_CAPACITY 8
#define INITIAL_DYNAMIC_STRING_CAPACITY 100

#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "libft.h"
//for development:
#include <string.h>
#include <stdio.h>
//#include <sys/types.h>
//#include <libgen.h>

typedef struct	s_dynamic_string
{
	char	*string;
	size_t	size;
	size_t	capacity;
}				t_vector;

typedef struct	t_dynamic_string
{
	char	**entries;
	size_t	size;
	size_t	capacity;
}				t_string_vector;

void	display_error_message(const char *error_message);

#endif
