NAME    = libft.a
CC      = cc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror

SRC     = ft_isalpha.c \
          ft_isdigit.c \
          ft_isalnum.c \
          ft_isascii.c \
          ft_isprint.c \
          ft_strlen.c \
          ft_memset.c \
          ft_bzero.c \
          ft_memcpy.c \
          ft_memmove.c \
          ft_strlcpy.c \
          ft_strlcat.c \
          ft_toupper.c \
          ft_tolower.c \
          ft_strchr.c \
          ft_strrchr.c \
          ft_strncmp.c \
          ft_memchr.c \
          ft_memcmp.c \
          ft_strnstr.c \
          ft_atoi.c \
          ft_calloc.c \
          ft_strdup.c \
          ft_substr.c \
          ft_strjoin.c \
          ft_strtrim.c \
          ft_split.c \
          ft_itoa.c \
          ft_strmapi.c \
          ft_striteri.c \
          ft_putchar_fd.c \
          ft_putstr_fd.c \
          ft_putendl_fd.c \
          ft_putnbr_fd.c \
		  ft_printf.c \
		  ft_printf.c \
		  ft_put_address.c \
		  ft_puthex.c \
		  ft_putnbr.c \
		  utilities.c \
		  get_next_line.c \
		  get_next_line_utils.c \
		  ft_strcmp.c \
		  ft_strjoin_many.c \
		  ft_ultoa.c \

SRCBONUS = ft_lstnew_bonus.c \
           ft_lstadd_front_bonus.c \
           ft_lstsize_bonus.c \
           ft_lstlast_bonus.c \
           ft_lstadd_back_bonus.c \
           ft_lstdelone_bonus.c \
           ft_lstclear_bonus.c \
           ft_lstiter_bonus.c \
           ft_lstmap_bonus.c

OBJ       = $(SRC:.c=.o)
OBJBONUS  = $(SRCBONUS:.c=.o)
LIBC      = ar rcs

# Colors
YELLOW	= \033[38;5;227m
RESET   = \033[0m
UP		= "\033[A""\033[K"

%.o: %.c
			echo "$(YELLOW) 🔧 Compiling ... $<$(RESET)"
			$(CC) $(CFLAGS) -c $< -o $@
			printf $(UP)

$(NAME):	$(OBJ)
			$(LIBC) $(NAME) $(OBJ)

all:		$(OBJ) $(OBJBONUS)
			$(LIBC) $(NAME) $(OBJ) $(OBJBONUS)

bonus:		$(OBJBONUS)
			$(LIBC) $(NAME) $(OBJBONUS)

clean:
			$(RM) *.o

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re bonus
