/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_qout_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:39 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:26:40 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_qout_nodes(t_node *node)
{
	int		i;
	char	*new_args;

	i = 0;
	while (node)
	{
		i = 0;
		while (node->args && node->args[i])
		{
			if (node->args[i][0] == '\'' || node->args[i][0] == '\"')
			{
				new_args = ft_strccpy(&node->args[i][1], node->args[i][0]);
				ft_restore_value(&node->args[i], &new_args, 1);
			}
			i++;
		}
		node = node->next;
	}
}

void	del_qout_cmd(char **cmd)
{
	int		i;
	char	*new_args;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		if (cmd[i][0] == '\'' || cmd[i][0] == '\"')
		{
			new_args = ft_strccpy(&cmd[i][1], cmd[i][0]);
			ft_restore_value(&cmd[i], &new_args, 1);
		}
		i++;
	}
}
