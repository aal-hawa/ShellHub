/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:27:30 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:28:36 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*malloc_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->redirect = NULL;
	token->cmd = NULL;
	token->next = NULL;
	token->is_bilt_cmd = 0;
	return (token);
}

t_node	*malloc_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->fd_name = NULL;
	node->next = NULL;
	node->type_before = NULL;
	return (node);
}

void	copy_node(t_node **to_node, t_node **from_node, int is_free_before)
{
	if (!from_node[0])
		return ;
	if (is_free_before == 1 && to_node[0]->type_before)
		to_node[0]->type_before = free_string(&to_node[0]->type_before);
	if (is_free_before == 1 && to_node[0]->fd_name)
		to_node[0]->fd_name = free_string(&to_node[0]->fd_name);
	if (is_free_before == 1 && to_node[0]->args)
		free_array2d(&(to_node[0]->args), 0);
	to_node[0]->type_before = ft_strdup(from_node[0]->type_before);
	to_node[0]->fd_name = ft_strdup(from_node[0]->fd_name);
	to_node[0]->next = from_node[0]->next;
	to_node[0]->args = copy_array2d(from_node[0]->args, 0);
}
