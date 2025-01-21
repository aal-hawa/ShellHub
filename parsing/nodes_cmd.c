/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:56:55 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/21 19:59:58 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *create_node(char **args, char type)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
	{
		free_nodes(&node);
        return NULL;
	}
    node->args = args;
    node->type = type;
    node->next = NULL;
    return (node);
}

char	**nodes_cmd()
{
	t_node	nodes;
}