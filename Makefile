NAME = minishell
LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = $(CFLAGS) -I$(LIBFT)/headers -L$(LIBFT) -lft 
LDFLAGS = -lreadline -lncurses

SRC_MAIN = main.c
SRC = minishell.c \
	builtins/cd.c builtins/echo.c builtins/env.c builtins/exit.c builtins/export.c builtins/pwd.c builtins/status_program.c builtins/unset.c \
	parsing/readline.c  parsing/double_qoutes.c parsing/new_node_2.c parsing/order_nodes.c parsing/check_valid_line.c \
	parsing/operators.c parsing/single_quotes.c parsing/variable_expansion.c parsing/fixed_line_spaces.c \
	parsing/tilde.c  parsing/check_valid_qout.c \
	utils/utils_array.c utils/ft_strclen.c utils/check_valid_input_exp.c \
	utils/ft_strccpy.c utils/ft_strlccpy.c utils/ft_strcmp.c utils/malloc_node.c utils/del_qout_nodes.c utils/ft_strjoin_path.c utils/ft_putstr_fd_malloc.c \
	utils/free_nodes.c utils/free_array2d.c utils/ft_restore_value.c utils/init_info.c utils/print_array2d.c utils/is_qout.c utils/builtins_message.c \
    utils/ft_strndup.c utils/free_info.c utils/utils_export.c \
	execution/r_wr_func.c execution/pipes.c execution/parent_func.c execution/execve.c execution/builtins.c execution/direct_in_output.c \
	execution/pipes_utils.c execution/get_path.c  execution/get_next_line.c execution/get_next_line_utils.c execution/execute.c execution/init_file.c execution/here_doc.c \
	signals/signals_handler.c

OBJS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

all: $(LIBFT_A)  $(NAME)

$(LIBFT_A): 
	make -C $(LIBFT)

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