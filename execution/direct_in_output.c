/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_in_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:51 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:21:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	utils_direct_fun(t_info *info)
{
	int	is_exit;

	is_exit = 0;
	if (info->fd_file_w == -1 || info->fd_file_r == -1)
	{
		info->status_exit = 1;
		info->fd_file_w = close_fd_fun(info->fd_file_w);
		info->fd_file_r = close_fd_fun(info->fd_file_r);
		info->fd_file_w = -2;
		info->fd_file_r = -2;
		is_exit = 1;
	}
	else
		info->status_exit = 0;
	return (is_exit);
}

int	direct_fun(t_node *node, t_info *info)
{
	if (!ft_strcmp(node->type_before, ">"))
		info->fd_file_w = open_file_w(node->args[0]);
	else if (!ft_strcmp(node->type_before, ">>"))
		info->fd_file_w = open_file_w_b(node->args[0]);
	else if (!ft_strcmp(node->type_before, "<"))
		init_files(node, info);
	else if (!ft_strcmp(node->type_before, "<<"))
		open_here_doc(node, info);
	return (utils_direct_fun(info));
}
