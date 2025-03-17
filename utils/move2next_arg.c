/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2next_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:27:33 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:27:34 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	**move2next_arg(t_node **cmd_node)
// {
// 	char	**new_args;

// 	new_args = copy_array2d(cmd_node[0]->args + 1, 0);
// 	free_array2d(&cmd_node[0]->args, 0);
// 	if (!new_args)
// 		return (NULL);
// 	cmd_node[0]->args = new_args;
// 	return (new_args);
// }
