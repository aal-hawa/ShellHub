NAME = minishell
LIBFT = libft
LIBFT_A = $(LIBFT)/libft.a
# NAME_BNS = minishell_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT)/headers
LDFLAGS = -lreadline -lncurses
SRC_MAIN = main.c 
# SRC_BNS = main_bonus.c 

SRC = minishell.c \
	parsing/readline.c parsing/tokens.c
OBGS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)
# OBGS =  $(SRC_MAIN:.c=.o)

# OBGS_BNS = $(SRC:.c=.o) $(SRC_BNS:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	make -C $(LIBFT)

$(NAME): $(OBGS)
	$(CC) $(OBGS) -o $(NAME) $(LDFLAGS)

# $(NAME_BNS): $(OBGS_BNS)
# 	$(CC) $(OBGS_BNS) -o $(NAME_BNS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	rm -f $(OBGS) $(OBGS_BNS)

fclean: clean
	make fclean -C $(LIBFT)
	rm -f $(NAME) $(NAME_BNS)

re: fclean all

bonus: $(NAME_BNS)

.PHONY: all clean fclean re bonus 