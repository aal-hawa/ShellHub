/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:22:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:07:17 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_files(t_node *node, t_info *info)
{
	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_r = open_file_r(node->args[0]);
}

int	open_all_files(t_node *node, t_info *info)
{
	t_node	*this_node;

	this_node = node;
	while (this_node)
	{
		if (direct_fun(this_node, info) == 1)
			return (1);
		this_node = this_node->next;
	}
	return (0);
}

int	check_open_files(t_token *token, t_info *info)
{
	int	is_exit;

	info->fd_file_r = close_fd_fun(info->fd_file_r);
	info->fd_file_w = close_fd_fun(info->fd_file_w);
	is_exit = 0;
	is_exit = open_all_files(token->redirect, info);
	if (is_exit == 1)
	{
		info->i_childs++;
		return (1);
	}
	return (0);
}
