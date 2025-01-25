NAME = minishell
LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS = $(CFLAGS) -I$(LIBFT)/headers -L$(LIBFT) -lft
LDFLAGS = -lreadline -lncurses

SRC_MAIN = main.c
SRC = minishell.c \
	parsing/readline.c \
	parsing/tokens.c \
	utils/free_malloc.c \
	utils/edit_in_split.c utils/ft_strclen.c \
	utils/ft_strccpy.c utils/ft_strcmp.c utils/ft_strlchr.c \
	utils/pre_split.c 
OBJS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)

all: $(LIBFT_A) $(NAME)

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
