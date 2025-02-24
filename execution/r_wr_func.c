
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
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r(node->args[0]);
	node->fd_file = info->fd_file_r; 
}

void	init_here_doc(t_node *node, t_info *info)
{
	char *str;
	char	*str_i;

	info->fd_file_r = close_fd_fun(info->fd_file_r);

	str_i = ft_itoa(info->index_files_crt);
	str = ft_strjoin("/tmp/tmp_shell_", str_i);
	info->fd_file_r = open_file_r_w(str);
	info->limiter = ft_strjoin_path(node->args[0], "\n", 0);
	info->i_limiter = ft_strlen(info->limiter);
	ft_putstr_fd_malloc(get_next_line(info), info->fd_file_r, 1);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	// if (info->fd_file_r >= 0)
	// 	close(info->fd_file_r);
	info->fd_file_r = open_file_r(str);
	node->fd_file = info->fd_file_r; 
	str_i = free_char(&str_i);
	str = free_char(&str);
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
	printf("opopopoopo\n");
	return (info->fd_file_r);
}
