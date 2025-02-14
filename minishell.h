
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

typedef struct s_node
{
    char **args;
    char *type_before;
    char *type_after;
    int is_dir_bilt_cmd;
	int	fd_file;
	char	*last_fd_name;
	int	is_do_execute;
    struct s_node *next;
} t_node;

typedef struct s_node_order
{
	t_node	*nodes_input;
	t_node	*nodes_output;
	t_node	*first_input;
	t_node	*first_output;
	char	**args;
	char	*str_cmd;
	char	*str_join;
	int		i;
} t_node_order;

typedef	struct s_colors
{
	char	*green_color;
	char	*default_color;
	char	*red_color;
	char	*blue_color;
	char	*yellow_color;
	char	*magenta_color;
	char	*cyan_color;
	char	*white_color;
}	t_colors;

typedef struct s_info
{
    int		i_fds;
	int		i_childs;
	int		i_wait;
	int		fd_file_r;
	int		fd_file_w;
	int		offset;
	int		ac;
	int		str_i;
	char	*env;
	char	*limiter;
	int		i_limiter;
	char	*path_commd;
	char	**envp;
	int		is_for_w;
	int		is_bonus;
	size_t	i_split;
	int		env_null;
	int		is_exit_one;

	// char	**env;
	char	*home;
    int     status_exit;
    char    *curent_path;
	int		index_files_crt;
	t_node	*first_node;
	t_colors	*colors;
}					t_info;

void	minishell(t_info *info);
char	*readline_fun();
char	**tokens_fun(char *line);
char	*cd_fun(char *cd, t_info *info);
char	*pwd_fun(t_info *info, int is_print);
void	exit_fun();
char	*echo_n_fun(char *str);
char	*echo_with_line_fun(char *str);
char	*env_fun(char *name);
int		export_fun(char *name, t_info *info);
int		unset_func(char *name, t_info *info);
int     is_operator_fun(char *str);
void	free_fun(char **str);
char	**add_in_split(char **split, char *add_str, int is_alpha);
char	**marge_2_splits(char **first_split, char **second_split);
char	**del_str_from_array2d(char **array2d, char *del_str, int size_str);
size_t	ft_strclen(const char *s, char to_char);
char	*ft_strccpy(char *str, char to_char);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_restore_value(char **dest, char **str, int is_str_malloc);
char	*ft_strlchr(char **str, char lst_char, int is_str_malloc);
// void	free_split(char **split, int len);
char    *pre_split(char **s, const char *ops);
t_node	*nodes_init(char **tokens, t_info *info);
void    free_nodes(t_node **nodes);
void	free_node(t_node **nodes);
void	init_info(int ac, char *env, char **envp, t_info *info);
void	reset_info(t_info *info);
t_node	*malloc_node();
int		len_split(char **split);
char	**copy_split(char **split);
void	copy_node(t_node **to_node, t_node **from_node, int is_free_before);
int		is_exist_str_in_2array(char **array2d, char *del_str, int size_str);
void	order_info_nodes(t_info *info);
void	dir_bilt_fun(t_node **node, char *before_tybe, t_info *info);
int		is_operator_input_fun(char *str);
int		is_operator_output_fun(char *str);
void	init_colors(t_colors *colors, t_info *info);


size_t		ft_strlen(const char *s);
char		**ft_split_p(char const *s, char c, t_info *info);
int			open_file_w(char *name_file);
// int			execute_fun(char **str, t_info *info);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strjoin_p(char const *s1, char const *s2, int is_path);
int			open_file_w_b(char *name_file);
void		env_data(char **envp, char **env, t_info *info);
// int			init_files(char **str, t_info *info);
void		init_files(t_node *node, t_info *info);
int			init_files_biultins(char *str, t_info *info);
void		init_here_doc(t_node *node, t_info *info);
void		error_pipe(int **fd1, int i, t_info *info, char **strs);
char		*get_next_line(t_info *info);
char		*ft_strjoin_g(char *s1, char *s2, int *is_done, t_info *info);
char		*free_char(char **this_string);
void		ft_putstr_fd_p(char *s, int fd, int is_malloc);
int			finish_parent(int ***fd, pid_t **frs, t_info *info);
void		de_allocate(int ***fd, pid_t **frs, int i);
void		free_split(char **dst, size_t i);
char		*ft_strdup(const char *str);
void		get_path_command(char **strs, t_info *info);
void		allocate_fds(int ***fd, pid_t **frs, int j);
void		print_nodes(t_node *nodes, t_colors *colors);
void		childs(t_node *node, int **fd1, pid_t *frs, t_info *info);
void		close_fds_childs(int **fd1, t_info *info);
int			execute_fun(t_info *info);
void		create_nodes(char *line, t_info *info);
#endif