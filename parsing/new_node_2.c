#include "../minishell.h"

int	is_biult_fun(char *first_arg)
{
	if (!ft_strcmp(first_arg, "cd")
		|| !ft_strcmp(first_arg, "pwd") 
		|| !ft_strcmp(first_arg, "echo")
		|| !ft_strcmp(first_arg, "env") 
		|| !ft_strcmp(first_arg, "export")
		|| !ft_strcmp(first_arg, "unset")
		|| !ft_strcmp(first_arg, "exit"))
		return (1);
	return (0);
}

void	dir_bilt_fun(t_node **node)
{
	if (!ft_strcmp(node[0]->type_before, "<")
		|| !ft_strcmp(node[0]->type_before,"<<")
		|| !ft_strcmp(node[0]->type_before,">")
		|| !ft_strcmp(node[0]->type_before,">>"))
		node[0]->is_dir_bilt_cmd = 0;
	else if (is_biult_fun(node[0]->args[0]) == 1)
		node[0]->is_dir_bilt_cmd = 1;
	else
		node[0]->is_dir_bilt_cmd = 2;
}

void	type_after_fun(t_node **node, char **line, int i)
{
	if (line[0][i] != '|' && line[0][i + 1])
	{
		if (line[0][i] == '>' && line[0][i + 1] == '>')
			node[0]->type_after = ft_strdup(">>");
		else if (line[0][i] == '<' && line[0][i + 1] == '<')
			node[0]->type_after = ft_strdup("<<");
	}
	else
	{
		node[0]->type_after = malloc(sizeof(char) * 2);
		node[0]->type_after[0] = line[0][i];
		node[0]->type_after[1] = '\0';
	}
}


char	*insert_node(t_node **node, char **line, int i, int j)
{
	char	*cmd_order;
	char	*before_tybe;
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
	before_tybe = node[0]->type_after;
	return (before_tybe);
}
t_node	*init_first_node(char *line, t_info *info)
{
	t_node	*node;
	
	if (!line)
		return (NULL);
	node = malloc_node();
	if (!node)
	{
		info->first_node = NULL;
		return (NULL);
	}
	node->type_before = ft_strdup("start");
	info->first_node = node;
	return (node);
}

void	create_nodes_without_order(char *line, t_node	**node)
{
	char	*before_tybe;
	int		i;
	int		j;
	int		is_qout;

	j = 0;
	i = -1;
	is_qout = 0;
	while (line[++i])
	{
		if (line[i] == '|' && is_qout == 0)
		{
			type_after_fun(node, &line, i);
			before_tybe = insert_node(node, &line, i, j);
			j = i;
			node[0]->next = malloc_node();
			*node = node[0]->next;
			node[0]->type_before = ft_strdup(before_tybe);
		}
		is_qout = is_qout_fun(is_qout, line[i]);
	}
	node[0]->type_after = ft_strdup("end");
	before_tybe = insert_node(node, &line, i, j);
	node[0]->next = NULL;
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;

	node = init_first_node(line, info);
	if (!node)
		return ;
	create_nodes_without_order(line, &node);
	order_info_nodes(info);
}
