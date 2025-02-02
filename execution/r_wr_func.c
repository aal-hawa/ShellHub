
# include "../minishell.h"

int	open_file_r(char *name_file)
{
	int	fd;

	fd = open(name_file, O_RDONLY, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_w(char *name_file)
{
	int	fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_w_b(char *name_file)
{
	int	fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_r_w(char *name_file)
{
	int	fd;

	fd = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
void	init_files(t_node *node, t_info *info)
{
	info->fd_file_r = open_file_r(node->args[0]);
}

// int	init_files(char **str, t_info *info)
// {
// 	info->offset = 2;
// 	if (ft_strncmp(str[1], "here_doc", 8) == 0 && info->is_bonus == 1)
// 	{
// 		info->offset = 3;
// 		info->fd_file_r = open_file_r_w("/tmp/tmp_pipe");
// 		info->limiter = ft_strjoin_p(str[2], "\n", 0);
// 		info->i_limiter = ft_strlen(info->limiter);
// 		ft_putstr_fd_p(get_next_line(info), info->fd_file_r, 1);
// 		if (info->fd_file_r != -1)
// 			close(info->fd_file_r);
// 		info->fd_file_r = open_file_r("/tmp/tmp_pipe");
// 	}
// 	else
// 	{
// 		info->fd_file_r = open_file_r(str[1]);
// 	}
// 	return (info->offset);
// }

void	init_here_doc(t_node *node, t_info *info)
{
	char *str;
	char	*str_i;

	str_i = ft_itoa(info->index_files_crt);
	str = ft_strjoin("/tmp/tmp_shell_", str_i);
	info->fd_file_r = open_file_r_w(str);
	info->limiter = ft_strjoin_p(node->args[0], "\n", 0);
	info->i_limiter = ft_strlen(info->limiter);
	ft_putstr_fd_p(get_next_line(info), info->fd_file_r, 1);
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
	info->fd_file_r = open_file_r(str);
	str_i = free_char(str_i);
	str = free_char(str);
}

int	init_files_biultins(char *str, t_info *info)
{
	info->fd_file_r = open_file_r_w("/tmp/tmp_biultins");
	ft_putstr_fd_p(str, info->fd_file_r, 1);
	if (info->fd_file_r != -1)
		close(info->fd_file_r);
	info->fd_file_r = open_file_r("/tmp/tmp_biultins");
	return (info->fd_file_r);
}