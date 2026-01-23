NAME = minishell

# Src files

# SRC = $(SRC_DIR)/ft_split_space.c \
	  $(SRC_DIR)/node_utilities.c \
	  $(SRC_DIR)/str_arr_utilities.c \
	  $(SRC_DIR)/error_handling.c \
	  $(SRC_DIR)/parser.c \

SRC = $(SRC_DIR)/main.c \
	  $(SRC_DIR)/init.c \
	  $(SRC_DIR)/shell_utilities.c \
	  $(SRC_DIR)/error_handling.c \
	  $(SRC_DIR)/str_utilities.c \
	  $(SRC_DIR)/build_prompt.c \
	  $(SRC_DIR)/cmd_list_utils.c \
	  $(SRC_DIR)/tokenizer.c \
	  $(SRC_DIR)/execute_comand.c \
	  $(SRC_DIR)/env_utilities.c \
	  $(SRC_DIR)/our_commands.c \

# -- Directories --

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Headers
HEADERS_DIR = headers

# Src
SRC_DIR = src

# Obj
OBJ_DIR = obj

# -----------------

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDLIBS = -lreadline
DFLAGS = -g3
MAKE_FLAGS = --silent --no-print-directory

# Colors
GREEN	= \033[38;5;84m
YELLOW	= \033[38;5;227m
RED		= \033[38;5;9m
BLUE	= \033[38;5;75m
BOLD	= \033[1m
RESET   = \033[0m
UP		= "\033[A""\033[K"

.SILENT:

all:		$(NAME)
			echo "$(GREEN) ✨ $(NAME) is up to date!$(RESET)"

$(NAME):	$(LIBFT) $(OBJ_DIR) $(OBJ)
			echo "$(YELLOW) 🔧 Compiling ... $(NAME)$(RESET)"
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -I$(LIBFT_DIR) -I$(HEADERS_DIR) -o $(NAME) $(LDLIBS)
			printf $(UP)
			echo "$(GREEN) ✅ Built $(NAME)$(RESET)"

$(LIBFT):	| $(LIBFT_DIR)
			echo "$(YELLOW) 🔧 Compiling ... $(LIBFT_DIR)$(RESET)"
			make $(MAKE_FLAGS) libft.a -C $(LIBFT_DIR)
			printf $(UP)
			echo "$(GREEN) ✅ Built $(LIBFT_DIR)$(RESET)"

$(LIBFT_DIR):
			echo "$(YELLOW) 📁 Cloning libft repository ...$(RESET)"
			git clone git@github.com:MaybeMaxim/libft.git >/dev/null 2>&1
			printf $(UP)
			echo "$(GREEN) ✅ Cloned libft$(RESET)"

$(OBJ_DIR):
			mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			echo "$(YELLOW) 🔧 Compiling ... $<$(RESET)"
			$(CC) $(CFLAGS) $(DFLAGS) -I$(LIBFT_DIR) -I$(HEADERS_DIR) -c $< -o $@
			printf $(UP)

clean:
			echo "$(RED) 🧹 Cleaning object files ...$(RESET)"
			rm -f $(OBJ)
			make clean $(MAKE_FLAGS) -C $(LIBFT_DIR)
			printf $(UP)
			echo "$(GREEN) 🗑️✨ Removed all object files$(RESET)"

fclean:
			echo "$(RED) 🧹 Deep cleaning project ...$(RESET)"
			rm -f $(OBJ) $(NAME)
			make fclean $(MAKE_FLAGS) -C $(LIBFT_DIR)
			printf $(UP)
			echo "$(GREEN) 🧽 Deep cleaning is complete$(RESET)"

allclean:
			echo "$(RED) 🧹🧽 Full cleaning project ...$(RESET)"
			rm -rf $(OBJ_DIR) $(NAME) $(LIBFT_DIR)
			printf $(UP)
			echo "$(GREEN) 🧹🧽 Full cleaning is complete$(RESET)"


run:		all
			./$(NAME) maps/map.ber

dbug:
			$(CC) $(CFLAGS) $(DFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(LDLIBS)
			gdb $(NAME)

re:
			echo "$(BLUE) 🔄 Rebuilding everything ...$(RESET)"
			make $(MAKE_FLAGS) fclean
			printf $(UP)
			make $(MAKE_FLAGS) all

.PHONY: all clean fclean re
