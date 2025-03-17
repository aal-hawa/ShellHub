/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:22:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:22:26 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_fun(t_info *info)
{
	int	exit_child;

	info->i_wait = 0;
	exit_child = 0;
	while (info->i_wait < info->str_i)
	{
		wait(&exit_child);
		info->status_exit = exit_child % 255;
		info->i_wait++;
	}
}

void	close_fds_parent(int **fd1, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->str_i + 1)
	{
		close(fd1[i][0]);
		close(fd1[i][1]);
		i++;
	}
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	if (info->limiter != NULL)
		free_string(&info->limiter);
}

void	finish_parent(t_info *info)
{
	if (info->str_i == 0)
		return ;
	close_fds_parent(info->fds, info);
	wait_fun(info);
	de_allocate(&info->fds, &info->frs, info->str_i);
}
