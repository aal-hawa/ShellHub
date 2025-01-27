
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

typedef struct s_node {
    char **args;
    char type_before;
    char type_after;
    struct s_node *next;
    int is_dir_bilt_cmd;
} t_node;


typedef struct s_info
{
	char	**env;
    int     status_exit;
    char    *curent_path;
}					t_info;

void	minishell();
char	*readline_fun();
char	**tokens_fun(char *line);
char	*cd_fun(char *cd, t_info *info);
char	*pwd_fun(t_info *info);
void	exit_fun();
void	echo_n_fun(char *str);
int     is_operator_fun(char *str);
void	free_fun(char **str);
char 	**add_in_split(char **split, char *add_str);
char 	**del_from_split(char **split, char *del_str);
size_t	ft_strclen(const char *s, char to_char);
char	*ft_strccpy(char *str, char to_char);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_restore_value(char **dest, char **str, int is_str_malloc);
char	*ft_strlchr(char **str, char lst_char, int is_str_malloc);
void	free_split(char **split, int len);
char    *pre_split(char **s, const char *ops);
t_node  *nodes_init(char **tokens);
#endif