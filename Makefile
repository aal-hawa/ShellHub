NAME = minishell
LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a
PIPEX_DIR = ../pipex
PIPEX_A = $(PIPEX_DIR)/pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = $(CFLAGS) -I$(LIBFT)/headers -L$(LIBFT) -lft
LDFLAGS = -lreadline -lncurses

SRC_MAIN = main.c
SRC = minishell.c \
	parsing/readline.c \
	parsing/tokens.c \
	utils/free_malloc.c \
	utils/edit_in_split.c utils/ft_strclen.c utils/ft_strccpy.c \
	utils/ft_strcmp.c utils/ft_strlchr.c \
OBJS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

all: $(LIBFT_A) $(PIPEX_A) $(NAME)

$(LIBFT_A): 
	make -C $(LIBFT)

$(PIPEX_A):
	make -C $(PIPEX_DIR)

$(NAME): $(OBJS) $(LIBFT_A) $(PIPEX_A)
	$(CC) $(OBJS) -o $(NAME) $(FLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	make clean -C $(PIPEX_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	make fclean -C $(PIPEX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
