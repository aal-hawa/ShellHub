/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:32:18 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 04:00:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

int	g_global_variable;

typedef struct s_node
{
	char			**args;
	char			*type_before;
	char			*fd_name;
	struct s_node	*next;
}					t_node;

typedef struct s_token
{
	t_node			*redirect;
	char			**cmd;
	int				is_bilt_cmd;
	struct s_token	*next;
}					t_token;

typedef struct s_node_order
{
	t_node			*nodes;
	t_node			*first_nodea;
	char			**args;
	char			*str_cmd;
	int				i;
}					t_node_order;

typedef struct s_info
{
	int				i_fds;
	int				i_childs;
	int				i_wait;
	int				fd_file_r;
	int				fd_file_w;
	int				str_i;
	char			*path_env;
	char			*limiter;
	int				i_limiter;
	char			*path_commd;
	char			**envp;
	char			**export;
	int				env_null;
	char			*home;
	int				status_exit;
	char			*curent_path;
	int				index_files_crt;
	int				**fds;
	char			**herdoc_files;
	pid_t			*frs;
	t_token			*tokens;
}					t_info;

void		minishell(t_info *info);
char		*readline_fun(void);
char		**cd_fun(char **args, t_info *info);
char		**pwd_fun(t_info *info, int is_print);
void		exit_fun(char **arg, t_info *info);
char		**echo_n_fun(char **args, int is_print);
char		**echo_with_line_fun(char **args, int is_print);
char		**env_fun(char **args, t_info *info, int is_print);
char		**export_fun(char **args, t_info *info, int is_print);
char		**unset_func(char **args, t_info *info);
char		**add_in_array2d(char ***array2d, char *add_str, int is_alpha);
char		**del_str_from_array2d(char ***array2d, char *del_str);
ssize_t		ft_strclen(const char *s, char to_char);
char		*ft_strccpy(char *str, char to_char);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strccmp(const char *s1, const char *s2, char c);
char		*ft_restore_value(char **dest, char **str, int is_str_malloc);
void		free_nodes(t_node **node);
void		free_node(t_node **node);
void		free_info(t_info *info);
void		init_info(char **envp, t_info *info);
void		reset_info(t_info *info);
t_node		*malloc_node(void);
int			len_array2d(char **array2d);
char		**copy_array2d(char **array2d, int is_newline);
char		**copy_array2d_export(char **array2d);
void		copy_node(t_node **to_node, t_node **from_node, int is_free_before);
int			is_exist_str_in_2array(char **array2d, char *str);
void		order_info_nodes(t_info *info, t_node **node);
int			is_biult_fun(char *first_arg);
int			is_operator_fun(char *str);
int			is_char_operator_fun(char c);
int			is_qout_fun(int last_is_qout, char c);
void		del_qout_nodes(t_node *node);
char		*doller_sign_fun(char **str, t_info *info);
char		*find_doller_sign_fun(char **str, t_info *info);
char		*merge_result_with_after_space(char *str_dollersign, char *str);
void		print_array2d(char **array2d, int is_with_newline);
void		print_array2d_fd(char **array2d, int fd);
int			check_valid_line(char **line, t_info *info);
char		*double_quot_fun(char **line, int i, char *str, t_info *info);
char		*single_quot_fun(char *str);
void		fixed_line_spaces(char **line);
char		*tilde(char **line, char *str_home);
char		*status_program_fun(char **str, t_info *info);
char		*chck_spacesbetween_qout(char **line);
int			is_valid_qout(char **line, t_info *info);
char		*builtins_error_message(char *str_tybe_builtins, char *str_input);
char		**builtins_message(char **str_massege, int is_print, int is_malloc);
int			direct_fun(t_node *node, t_info *info);
int			do_builtins(t_token *token, char ***result_blts, t_info *info);
void		for_execve(t_token *token, t_info *info);
int			open_file_r_w(char *name_file);
int			open_file_r(char *name_file);
int			close_fd_fun(int fd2close);
void		unlink_files(t_info *info);
void		exit_number(int exit_status, int is_de_allocate, t_info *info);
void		open_here_doc(t_node *node, t_info *info);
char		**make_export_fun(char **export);
t_token		*malloc_token(void);
void		del_qout_cmd(char **cmd);
char		*new_name_herdoc(int index);
void		free_tokens(t_token **token);
char		*join_with_restore(char **dst, char *s1, char *s2, char *s3);
void		ft_add_qout_export(char **str, int len);
void		execve_no_cmd(t_info *info);
int			check_echo_n(char *str);
size_t		ft_strlen(const char *s);
int			open_file_w(char *name_file);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strjoin_path(char const *s1, char const *s2, int is_path);
int			open_file_w_b(char *name_file);
void		env_data(t_info *info);
void		init_files(t_node *node, t_info *info);
void		init_here_doc(char *herdoc_file, t_info *info);
void		error_pipe(int **fds, int i, t_info *info);
char		*get_next_line(t_info *info);
char		*strjoin_herdoc(char **s1, char *s2, int *is_done, t_info *info);
char		*free_string(char **this_string);
void		ft_putstr_fd_malloc(char *s, int fd, int is_malloc);
void		finish_parent(t_info *info);
void		de_allocate(int ***fd, pid_t **frs, int i);
void		free_array2d(char ***dst, size_t i);
char		*ft_strdup(const char *str);
void		get_path_command(char **strs, t_info *info);
void		allocate_fds(int ***fd, pid_t **frs, int j, t_info *info);
void		childs(t_token *token, t_info *info);
void		close_fds_childs(int **fds, t_info *info);
void		execute_fun(t_info *info);
void		create_nodes(char *line, t_info *info);
char		*ft_strndup(const char *s, size_t n);
int			check_is_valid_key(char *str);
void		put_name_herdoc_files(t_info *info);
void		open_herdoc_files(char **herdoc_files, t_info *info);
char		*new_name_herdoc(int index);
int			open_all_files(t_node *node, t_info *info);
int			check_open_files(t_token *token, t_info *info);
void		do_builtins_check_fork(t_token *token, t_info *info,
				char ***result_blts);
int			init_pipes(t_info *info);
char		*ft_strlccpy(char *str, char devide_char);
int			to_lower_pwd_env(char *str);

#endif