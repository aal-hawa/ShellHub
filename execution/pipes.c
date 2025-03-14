
# include "../minishell.h"

int	close_fd_fun(int fd2close)
{
	if (fd2close >= 0)
	{
		close(fd2close);
		return (-2);
	}
	return (fd2close);
}

void	close_fds_childs(int **fds, t_info *info)
{
	int	j;

	j = 0;
	while (j < info->str_i + 1)
	{
		if (info->i_childs != j)
			close(fds[j][0]);
		if (info->i_childs + 1 != j)
			close(fds[j][1]);
		j++;
	}
}

void	child_execve(t_token *token, char **strs, t_info *info)
{
	if (info->fd_file_w >= 0)
	{
		dup2(info->fd_file_w, STDOUT_FILENO);
		info->fd_file_w = close_fd_fun(info->fd_file_w);
	}
	else if (token->next)
		dup2(info->fds[info->i_childs + 1][1], STDOUT_FILENO);
	close(info->fds[info->i_childs + 1][1]);
	execve(info->path_commd, strs, info->envp);
	perror(info->path_commd);
	de_allocate(&info->fds, &info->frs, info->str_i);
	free_array2d(&strs, 0);
	exit_number(1, 0, info);
}

void	dup_stdin_fileno(t_info *info)
{
	if (info->fd_file_r >= 0)
	{
		dup2(info->fd_file_r, STDIN_FILENO);
		info->fd_file_r = close_fd_fun(info->fd_file_r);
	}
	else if (info->i_childs != 0)
		dup2(info->fds[info->i_childs][0], STDIN_FILENO);
}

void	childs(t_token *token, t_info *info)
{
	char	**strs;

	strs = token->cmd;
	if (!strs)
	{
		error_pipe(info->fds, -3, info);
		de_allocate(&info->fds, &info->frs, info->str_i);
		return (exit_number(1, 0, info));
	}
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd_malloc(
				ft_strjoin_path("zsh: command not found: ", strs[0], 0), 2, 2);
		error_pipe(info->fds, -3, info);
		de_allocate(&info->fds, &info->frs, info->str_i);
		return (exit_number(127, 0, info));
	}
	dup_stdin_fileno(info);
	close(info->fds[info->i_childs][0]);
	child_execve(token, strs, info);
	exit_number(0, 0, info);
}
