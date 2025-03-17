/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:22:35 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:03:30 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	init_pipes(t_info *info)
{
	int		**fds;
	pid_t	*frs;

	fds = NULL;
	frs = NULL;
	allocate_fds(&fds, &frs, info->str_i);
	info->fds = fds;
	info->frs = frs;
	info->i_fds = 0;
	while (info->i_fds < info->str_i + 1)
	{
		if (pipe(fds[info->i_fds++]) == -1)
		{
			error_pipe(fds, --info->i_fds, info);
			de_allocate(&fds, &frs, info->str_i);
			exit_number(1, 0, info);
			return (1);
		}
	}
	return (0);
}
