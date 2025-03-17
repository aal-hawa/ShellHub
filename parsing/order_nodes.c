/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:27 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:28 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_node_order(t_node_order *node_order, t_node **current_node)
{
	node_order->nodes = NULL;
	node_order->first_nodea = NULL;
	node_order->args = current_node[0]->args;
	node_order->str_cmd = NULL;
	node_order->nodes = malloc_node();
	if (!node_order->nodes)
	{
		if (node_order->nodes)
			free_node(&node_order->nodes);
		return (0);
	}
	node_order->first_nodea = node_order->nodes;
	node_order->i = 0;
	return (1);
}

void	do_operator(t_node_order *node_order, t_node **nodes, t_info *info)
{
	if (nodes[0]->args)
	{
		nodes[0]->next = malloc_node();
		nodes[0] = nodes[0]->next;
	}
	nodes[0]->type_before = ft_strdup(node_order->args[node_order->i]);
	node_order->i++;
	nodes[0]->args = ft_split(node_order->args[node_order->i], ' ');
	if (!ft_strcmp(nodes[0]->type_before, "<<"))
		info->herdoc_files = add_in_array2d(&info->herdoc_files,
				nodes[0]->args[0], 0);
}

void	make_order_nodes(t_node_order *node_order, t_info *info)
{
	while (node_order->args[node_order->i])
	{
		if (is_operator_fun(node_order->args[node_order->i]) > 0)
			do_operator(node_order, &(node_order->nodes), info);
		else
		{
			if (node_order->str_cmd)
				node_order->str_cmd = join_with_restore(&node_order->str_cmd,
						node_order->str_cmd, " ",
						node_order->args[node_order->i]);
			else
				node_order->str_cmd = join_with_restore(&node_order->str_cmd,
						node_order->str_cmd, node_order->args[node_order->i],
						NULL);
		}
		if (node_order->args[node_order->i])
			node_order->i++;
	}
}

void	order_nodes(t_node **current_node, t_token **token, t_info *info)
{
	t_node_order	node_order;
	char			**array2d;

	if (!init_node_order(&node_order, current_node))
		return ;
	make_order_nodes(&node_order, info);
	array2d = ft_split(node_order.str_cmd, ' ');
	token[0]->cmd = array2d;
	if (token[0]->cmd && is_biult_fun(token[0]->cmd[0]) == 0)
		token[0]->is_bilt_cmd = 1;
	if (!node_order.first_nodea->args)
		free_nodes(&(node_order.first_nodea));
	token[0]->redirect = node_order.first_nodea;
	node_order.str_cmd = free_string(&node_order.str_cmd);
}

void	order_info_nodes(t_info *info, t_node **node)
{
	t_node	*next_node;
	t_token	*tokens;

	tokens = malloc_token();
	info->tokens = tokens;
	next_node = NULL;
	if (*node)
		next_node = *node;
	while (next_node)
	{
		order_nodes(&next_node, &tokens, info);
		del_qout_nodes(tokens->redirect);
		del_qout_cmd(tokens->cmd);
		next_node = next_node->next;
		if (next_node)
		{
			tokens->next = malloc_token();
			tokens = tokens->next;
		}
	}
}
