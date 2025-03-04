
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

void	child_execve(int **fds, char **strs, pid_t *frs, t_info *info)
{
	printf ("info->is_for_w: %d\n", info->is_for_w);
	if (info->is_for_w == 2)
		dup2(fds[info->i_childs + 1][1], STDOUT_FILENO);
		// else if (info->is_for_w == 1)
	else if (info->fd_file_w >=0 )
		dup2(info->fd_file_w, STDOUT_FILENO);
	close(fds[info->i_childs + 1][1]);
	if (info->is_for_w == 1)
		info->fd_file_w = close_fd_fun(info->fd_file_w);
	
	execve(info->path_commd, strs, info->envp);
	perror(info->path_commd);
	de_allocate(&fds, &frs, info->str_i);
	free_array2d(&strs, 0);
	exit_number(1, info);
}

void	dup_stdin_fileno(t_node *node, int **fds, t_info *info)
{
	if (node->is_no_inpipe == 1)
	{

		info->fd_file_w = open_file_r_w("/tmp/tmp_no_inpipe");
		dup2(info->fd_file_w, STDIN_FILENO);
		info->fd_file_w = close_fd_fun(info->fd_file_w);
		node->is_no_inpipe = 0;
		// info->str_i++;
		// unlink("/tmp/tmp_no_inpipe");
	}
	else
	{
		if (info->fd_file_r >= 0) //info->is_builtins_file == 2 && 
		{
			dup2(info->fd_file_r, STDIN_FILENO);
			info->fd_file_r = close_fd_fun(info->fd_file_r);
			info->is_builtins_file = 0;
		}
		else if (info->i_childs != 0 || (info->i_childs == 0 && node->is_no_inpipe == 1)) //info->i_childs != 0
		{

			dup2(fds[info->i_childs][0], STDIN_FILENO);
		}
	}
}

void	childs(t_node *node, int **fds, pid_t *frs, t_info *info)
{
	char	**strs;

	strs = node->args;
	if (!strs)
	{
		error_pipe(fds, -3, info);
		de_allocate(&fds, &frs, info->str_i);
		return (exit_number(1, info));
	}
	get_path_command(strs, info);
	if (!info->path_commd)
	{
		if (info->env_null == 1)
			ft_putstr_fd_malloc(
				ft_strjoin_path("zsh: command not found: ", strs[0], 0), 2, 2);
		error_pipe(fds, -3, info);
		de_allocate(&fds, &frs, info->str_i);
		return (exit_number(127, info));
	}
	dup_stdin_fileno(node, fds, info);
	close(fds[info->i_childs][0]);
	child_execve(fds, strs, frs, info);
	exit_number(0, info);
}
