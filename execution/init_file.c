# include "../minishell.h"

void	init_files(t_node *node, t_info *info)
{
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r(node->args[0]);
}

void	open_here_doc(t_node *node, t_info *info)
{
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	if (node->fd_name)
		info->fd_file_r = open_file_r(node->fd_name);
}

char	*new_name_herdoc(int index)
{
	char 	*str;
	char	*str_i;

	str_i = ft_itoa(index);
	str = ft_strjoin("/tmp/tmp_shell_", str_i);
	str_i = free_string(&str_i);
	return (str);
}

void	init_here_doc(char *herdoc_file, t_info *info)
{
	char 	*str;

	info->fd_file_r = close_fd_fun(info->fd_file_r);
	str = new_name_herdoc(info->index_files_crt);
	info->index_files_crt++;
	info->fd_file_r = open_file_r_w(str);
	info->limiter = ft_strjoin(herdoc_file, "\n");
	info->i_limiter = ft_strlen(info->limiter);
	ft_putstr_fd_malloc(get_next_line(info), info->fd_file_r, 1);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	str = free_string(&str);
}
