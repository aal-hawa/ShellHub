
# include "../minishell.h"

int	close_fd_fun(int fd2close)
{
	if (fd2close >= 0)
	{
		printf ("closed fd_file_r\n");
		close(fd2close);
		return (-2);
	}
	return (fd2close);
}

void	close_fds_childs(int **fds, t_info *info)
{
	int	j;

	j = 0;
	while (j < info->str_i + 1) // why with plus one
	{
		if (info->i_childs != j)
			close(fds[j][0]);
		if (info->i_childs + 1 != j)
			close(fds[j][1]);
		j++;
	}
	// if (info->fd_file_r >= 0) //info->i_childs == 0 && 
	// 	dup2(info->fd_file_r, STDIN_FILENO);
 	// info->fd_file_r = close_fd_fun(info->fd_file_r);
}

void	child_execve(int **fds, char **strs, pid_t *frs, t_info *info)
{
	// printf ("info->is_for_w: %d\n", info->is_for_w);
	if (info->is_for_w == 2)
		dup2(fds[info->i_childs + 1][1], STDOUT_FILENO);
	else if (info->is_for_w == 1)
		dup2(info->fd_file_w, STDOUT_FILENO);
	// else
	// 	dup2(1, STDOUT_FILENO);
	close(fds[info->i_childs + 1][1]);
	if (info->is_for_w == 1)
		info->fd_file_w = close_fd_fun(info->fd_file_w);

	// if (info->is_for_w == 1)
	// 	close(info->fd_file_w);
	execve(info->path_commd, strs, info->envp);
	perror(info->path_commd);
	de_allocate(&fds, &frs, info->str_i);
	free_array2d(&strs, 0);
	free_char(&info->path_commd);
	exit(1);
}

void	childs(t_node *node, int **fds, pid_t *frs, t_info *info)
{
	char	**strs;

	printf ("info->is_builtins_file: %d\n", info->is_builtins_file);
	printf ("info->fd_file_r: %d\n", info->fd_file_r);
	strs = node->args;
	if (!strs)
	{
		error_pipe(fds, -3, info, NULL);
		de_allocate(&fds, &frs, info->str_i);
		return (exit(1));
	}
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd_malloc(
				ft_strjoin_path("zsh: command not found: ", strs[0], 0), 2, 2);
		error_pipe(fds, -3, info, strs);
		de_allocate(&fds, &frs, info->str_i);
		return (exit(127));
	}


	if (info->fd_file_r >= 0) //info->is_builtins_file == 2 && 
	{
		dup2(info->fd_file_r, STDIN_FILENO);
		info->fd_file_r = close_fd_fun(info->fd_file_r);
		info->is_builtins_file = 0;
	}
	else //if (info->i_childs != 0 && info->is_no_inpipe == 0) //&& info->is_no_inpipe == 0
	{
		printf ("aaaaaaaaaaaaaaaaaaaaaaaaa1\n");
		dup2(fds[info->i_childs][0], STDIN_FILENO);
	}
	info->is_no_inpipe = 0;
	close(fds[info->i_childs][0]);
	child_execve(fds, strs, frs, info);
	exit(0);
}
