NAME = minishell
# NAME_BNS = minishell_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline -lncurses
SRC_MAIN = main.c 
# SRC_BNS = main_bonus.c 

SRC = minishell.c \
	parsing/readline.c parsing/tokens.c
OBGS = $(SRC:.c=.o) $(SRC_MAIN:.c=.o)
# OBGS =  $(SRC_MAIN:.c=.o)

# OBGS_BNS = $(SRC:.c=.o) $(SRC_BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBGS)
	$(CC) $(OBGS) -o $(NAME) $(LDFLAGS)

# $(NAME_BNS): $(OBGS_BNS)
# 	$(CC) $(OBGS_BNS) -o $(NAME_BNS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBGS) $(OBGS_BNS)

fclean: clean
	rm -f $(NAME) $(NAME_BNS)

re: fclean all

bonus: $(NAME_BNS)

.PHONY: all clean fclean re bonus 