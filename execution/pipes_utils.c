
# include "../minishell.h"

void	free_splits(char **strs)
{
	int	i;

	if (strs)
	{
		i = 0;
		while (strs[i])
		{
			strs[i] = free_string(&strs[i]);
			i++;
		}
		free(strs);
		strs = NULL;
	}
}

void	error_pipe(int **fds, int i, t_info *info)
{
	if (i == -3)
	{
		close(fds[info->i_childs][0]);
		close(fds[info->i_childs + 1][1]);
	}
	while (i >= 0)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i--;
	}
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	if (info->path_commd)
		free_string(&info->path_commd);
}

void	de_allocate(int ***fd, pid_t **frs, int i)
{
	if (fd && *fd && i >= 0)
	{
		while (i >= 0)
			free(fd[0][i--]);
		free(*fd);
		*fd = NULL;
	}
	if (frs && *frs)
	{
		free(*frs);
		*frs = NULL;
	}
}

void	allocate_fds(int ***fd, pid_t **frs, int j)
{
	int	i;

	i = 0;
	*fd = malloc(sizeof(int *) * (j + 1));
	if (!*fd)
		exit(1);
	*frs = malloc(sizeof(pid_t) * j);
	if (!*frs)
	{
		free(*fd);
		exit(1);
	}
	while (i < j + 1)
	{
		fd[0][i] = malloc(sizeof(int) * (2));
		if (!fd[0][i])
		{
			while (--i >= 0)
				free(fd[0][i]);
			free(*fd);
			free(*frs);
			exit(1);
		}
		i++;
	}
}
