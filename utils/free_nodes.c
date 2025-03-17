/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:26:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:30:34 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens(t_token **token)
{
	t_token	*temp;

	if (!token || !*token)
		return ;
	while (token[0])
	{
		if (token[0]->cmd)
			free_array2d(&(token[0]->cmd), 0);
		if (token[0]->redirect)
			free_nodes(&token[0]->redirect);
		temp = token[0];
		token[0] = token[0]->next;
		free(temp);
	}
}

void	free_nodes(t_node **node)
{
	t_node	*temp;

	if (!node || !*node)
		return ;
	while (node[0])
	{
		if (node[0]->args)
			free_array2d(&(node[0]->args), 0);
		if (node[0]->type_before)
			node[0]->type_before = free_string(&(node[0]->type_before));
		if (node[0]->fd_name)
			node[0]->fd_name = free_string(&(node[0]->fd_name));
		temp = node[0];
		node[0] = node[0]->next;
		free(temp);
	}
}

void	free_node(t_node **node)
{
	if (!node || !node[0])
		return ;
	if (node[0]->args)
		free_array2d(&(node[0]->args), 0);
	if (node[0]->type_before)
		node[0]->type_before = free_string(&(node[0]->type_before));
	if (node[0]->fd_name)
		node[0]->fd_name = free_string(&(node[0]->fd_name));
	free(*node);
	*node = NULL;
}
