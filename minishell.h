
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
	char	*fd_name;
	//for execute, equal zero nothing, equal one from direct and node next = NULL or only this node have more one args; but if the second args equal builtins it will be equal -1, equal two from builtins and type after = operators
	int	is_do_execute;
	char	**result_builtins;
	int	is_no_inpipe;
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
	char	**export;
	//for write in pipe, equal zero nothing, equal one for write in file, equal two for pipe
	int		is_for_w;
	int		is_bonus;
	// size_t	i_split;
	int		env_null;
	int		is_exit_one;
	//for builtins, equal zero nothing, equal one type after = operators not pipe, equal two type after = pipe
	int		is_builtins_file;
	char	*home;
    int     status_exit;
    char    *curent_path;
	int		index_files_crt;
	int		**fds;
	pid_t	*frs;
	// int		is_no_inpipe;
	t_node	*first_node;
	t_colors	*colors;
}					t_info;

void	minishell(t_info *info);
char	*readline_fun();
char	**tokens_fun(char *line);
char	**cd_fun(char **args, t_info *info);
char	**pwd_fun(t_info *info, int is_print);
void	exit_fun(char **arg, t_info *info);
char	**echo_n_fun(char **args, int is_print);
char	**echo_with_line_fun(char **args, int is_print);
char	**env_fun(char **args, t_info * info, int is_print);
char	**export_fun(char **args, t_info *info, int is_print);
char	**unset_func(char **args, t_info *info);
void	free_fun(char **str);
char	**add_in_split(char **split, char *add_str, int is_alpha);
char	**marge_2_splits(char ***first_split, char ***second_split);
char	**del_str_from_array2d(char **array2d, char *del_str, int size_str);
ssize_t	ft_strclen(const char *s, char to_char);
char	*ft_strccpy(char *str, char to_char);
void	ft_strccpy_free(char **str, char to_char);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strccmp(const char *s1, const char *s2, char c);
char	*ft_restore_value(char **dest, char **str, int is_str_malloc);
char	*ft_strlchr(char **str, char lst_char, int is_str_malloc);
// void	free_split(char **split, int len);
char    *pre_split(char **s, const char *ops);
// t_node	*nodes_init(char **tokens, t_info *info);
void	free_nodes(t_node **node);
void	free_node(t_node **node);
void	free_info(t_info *info);
void	init_info(int ac, char *env, char **envp, t_info *info);
void	reset_info(t_info *info);
t_node	*malloc_node();
t_node	*malloc_node2();
int		len_split(char **split);
char	**copy_split(char **split);
void	copy_node(t_node **to_node, t_node **from_node, int is_free_before);
int		is_exist_str_in_2array(char **array2d, char *del_str, int size_str);
void	order_info_nodes(t_info *info);
void	dir_bilt_fun(t_node **node);
int		is_biult_fun(char *first_arg);
int     is_operator_fun(char *str);
int		is_operator_input_fun(char *str);
int		is_operator_output_fun(char *str);
int		is_char_operator_fun(char c);
int		is_qout_fun(int last_is_qout, char c);
void	del_qout_nodes(t_node *node);
char	*doller_sign_fun(char **str, t_info *info);
char	*find_doller_sign_fun(char **str, t_info *info);
char	*marge_doller_sign(char *str_dollersign, char *str);
void	init_colors(t_colors *colors, t_info *info);
int		parsing_input(char **line);
void	print_array2d(char **array2d, int is_with_newline);
void	print_array2d_fd(char **array2d, int fd);
int		check_valid_line(char **line, t_info *info);
char	*double_quot_fun(char **line, int i, char *str, t_info *info);
char	*single_quot_fun(char *str);
void	fixed_line_spaces(char **line);
char	*marge_new_line(char **line, char **str_be4, char **str_after, char *str_changed);
char	*tilde(char **line, char *str_home);
char	*status_program_fun(char **str, t_info *info);
char	*chck_spacesbetween_qout(char **line);
int		is_valid_qout(char **line, t_info *info);
char	*builtins_error_message(char *str_tybe_builtins, char *str_input);
char	**builtins_Message(char **str_massege, int is_print, int is_malloc);
int		direct_fun(t_node *node, t_info *info);
void	do_builtins(t_node *node, char ***result_blts, t_info *info);
int		is_can_do_execve(t_node **node,t_node **cmd_node, t_info *info);
void	for_execve(t_node *node, int **fds, pid_t *frs, t_info *info, char **result_blts, t_node **cmd_node);
char	**move2next_arg(t_node **cmd_node);
int		open_file_r_w(char *name_file);
int		open_file_r(char *name_file);
int		close_fd_fun(int fd2close);
void	unlink_files(t_info *info);
void	exit_number(int exit_status, t_info * info);


size_t		ft_strlen(const char *s);
// char		**ft_split_p(char const *s, char c, t_info *info);
int			open_file_w(char *name_file);
// int			execute_fun(char **str, t_info *info);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strjoin_path(char const *s1, char const *s2, int is_path);
int			open_file_w_b(char *name_file);
void		env_data(char **envp, char **env, t_info *info);
// int			init_files(char **str, t_info *info);
void		init_files(t_node *node, t_info *info);
int			init_files_biultins(char **str, t_info *info);
void		init_here_doc(t_node *node, t_info *info);
void		error_pipe(int **fds, int i, t_info *info);
char		*get_next_line(t_info *info);
char		*ft_strjoin_g(char *s1, char *s2, int *is_done, t_info *info);
char		*free_string(char **this_string);
void		ft_putstr_fd_malloc(char *s, int fd, int is_malloc);
int			finish_parent(int ***fd, pid_t **frs, t_info *info);
void		de_allocate(int ***fd, pid_t **frs, int i);
void		free_array2d(char ***dst, size_t i);
char		*ft_strdup(const char *str);
void		get_path_command(char **strs, t_info *info);
void		allocate_fds(int ***fd, pid_t **frs, int j);
void		print_nodes(t_node *nodes, t_colors *colors);
void		childs(t_node *node, int **fds, pid_t *frs, t_info *info);
void		close_fds_childs(int **fds, t_info *info);
int			execute_fun(t_info *info);
void		create_nodes(char *line, t_info *info);
char		*ft_strndup(const char *s, size_t n);
int			check_is_valid_key(char *str);
void	show_leek(t_info *info);

#endif