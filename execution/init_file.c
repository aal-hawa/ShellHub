# include "../minishell.h"

void	init_files(t_node *node, t_info *info)
{
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r(node->args[0]);
	node->fd_file = info->fd_file_r; 
}

void	init_here_doc(t_node *node, t_info *info)
{
	char 	*str;
	char	*str_i;

	info->fd_file_r = close_fd_fun(info->fd_file_r);

	str_i = ft_itoa(info->index_files_crt);
	info->index_files_crt++;
	str = ft_strjoin("/tmp/tmp_shell_", str_i);
	info->fd_file_r = open_file_r_w(str);
	info->limiter = ft_strjoin_path(node->args[0], "\n", 0);
	info->i_limiter = ft_strlen(info->limiter);
	ft_putstr_fd_malloc(get_next_line(info), info->fd_file_r, 1);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	// info->fd_file_r = open_file_r(str);
	// node->fd_file = info->fd_file_r; 
	str_i = free_string(&str_i);
	node->fd_name = str;
	// str = free_string(&str);
}

int	init_files_biultins(char **str, t_info *info)
{
	int	i;

	i = 0;
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r_w("/tmp/tmp_biultins");
	while(str[i])
		ft_putstr_fd(str[i++], info->fd_file_r);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r("/tmp/tmp_biultins");
	return (info->fd_file_r);
}
