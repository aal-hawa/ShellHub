/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:49 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:28:51 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_info(t_info *info)
{
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	if (info->envp)
		free_array2d(&info->envp, 0);
	if (info->export)
		free_array2d(&info->export, 0);
	if (info->herdoc_files)
		free_array2d(&info->herdoc_files, 0);
	if (info->limiter)
		info->limiter = free_string(&info->limiter);
	if (info->path_commd)
		info->path_commd = free_string(&info->path_commd);
	if (info->curent_path)
		info->curent_path = free_string(&info->curent_path);
	if (info->tokens)
		free_tokens(&info->tokens);
}
