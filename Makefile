NAME = minishell
LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a
# PIPEX_DIR = ../pipex
# PIPEX_A = $(PIPEX_DIR)/pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = $(CFLAGS) -I$(LIBFT)/headers -L$(LIBFT) -lft 
LDFLAGS = -lreadline -lncurses

SRC_MAIN = main.c
SRC = minishell.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/status_program.c builtins/unset.c \
	parsing/readline.c 	parsing/tokens.c parsing/double_qoutes.c parsing/nodes_cmd.c parsing/new_node.c \
	parsing/operators.c parsing/single_quotes.c parsing/syntax_errors.c parsing/variable_expansion.c \
	utils/free_malloc.c	utils/edit_in_split.c utils/ft_strclen.c \
	utils/ft_strccpy.c utils/ft_strcmp.c utils/ft_strlchr.c utils/malloc_node.c \
	utils/free_nodes.c utils/free_split.c utils/ft_restore_value.c utils/init_info.c utils/pre_split.c \
	execution/ft_split.c execution/libft_func.c execution/r_wr_func.c execution/pipes.c execution/parent_func.c \
	execution/pipes_utils.c execution/get_path.c  execution/get_next_line.c execution/get_next_line_utils.c execution/execute.c \

OBJS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

all: $(LIBFT_A)  $(NAME)

$(LIBFT_A): 
	make -C $(LIBFT)

# $(PIPEX_A):
# 	make -C $(PIPEX_DIR)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
