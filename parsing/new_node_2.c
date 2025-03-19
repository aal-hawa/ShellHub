/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:22 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 03:04:20 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	to_lower_pwd_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (2);
	return (0);
}

int	is_biult_fun(char *first_arg)
{
	if (!ft_strcmp(first_arg, "cd") || to_lower_pwd_env(first_arg) == 1
		|| !ft_strcmp(first_arg, "echo") || to_lower_pwd_env(first_arg) == 2
		|| !ft_strcmp(first_arg, "export") || !ft_strcmp(first_arg, "unset")
		|| !ft_strcmp(first_arg, "exit"))
		return (1);
	return (0);
}

void	insert_node(t_node **node, char **line, int i, int j)
{
	char	*cmd_order;
	int		x;

	x = 0;
	if (j != 0)
		j++;
	cmd_order = malloc(sizeof(char) * (i - j + 1));
	while (j < i)
	{
		cmd_order[x] = line[0][j];
		j++;
		x++;
	}
	cmd_order[x] = '\0';
	node[0]->args = ft_split(cmd_order, ' ');
	free(cmd_order);
}

void	create_nodes_without_order(char *line, t_node *node)
{
	int	i;
	int	j;
	int	is_qout;

	j = 0;
	i = -1;
	is_qout = 0;
	while (line[++i])
	{
		if (line[i] == '|' && is_qout == 0)
		{
			insert_node(&node, &line, i, j);
			j = i;
			node->next = malloc_node();
			node = node->next;
			node->type_before = ft_strdup("|");
		}
		is_qout = is_qout_fun(is_qout, line[i]);
	}
	insert_node(&node, &line, i, j);
	node->next = NULL;
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;

	if (!line)
		return ;
	node = malloc_node();
	if (!node)
		return ;
	node->type_before = ft_strdup("start");
	create_nodes_without_order(line, node);
	order_info_nodes(info, &node);
	free_nodes(&node);
}
