#ifndef EXPANSION_H
#define EXPANSION_H

#define INITIAL_STRING_VECTOR_CAPACITY 8

#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include "libft.h"
//for development:
#include <string.h>
#include <stdio.h>
//#include <sys/types.h>
//#include <libgen.h>

typedef struct	s_string_vector
{
	char	**entries;
	size_t	size;
	size_t	capacity;
}				t_string_vector;

void	display_error_message(const char *error_message);

#endif
