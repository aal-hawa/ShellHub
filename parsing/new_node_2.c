#include "../minishell.h"

void	dir_bilt_fun(t_node **node, char *before_tybe)
{
	if (ft_strcmp(before_tybe, "start") && ft_strcmp(before_tybe,"|"))
		node[0]->is_dir_bilt_cmd = 0;
	else if (!ft_strcmp(node[0]->args[0], "cd") || !ft_strcmp(node[0]->args[0], "pwd") 
		|| !ft_strcmp(node[0]->args[0], "echo") || !ft_strcmp(node[0]->args[0], "env") || !ft_strcmp(node[0]->args[0], "export")
			||!ft_strcmp(node[0]->args[0], "unset") || !ft_strcmp(node[0]->args[0], "exit"))
		node[0]->is_dir_bilt_cmd = 1;
	else 
		node[0]->is_dir_bilt_cmd = 2;
}
void	type_after_fun(t_node **node, char **line, int i)
{

	if (line[0][i] != '|' && line[0][i + 1])
	{
		if (line[0][i] == '>' && line[0][i + 1] == '>')
			node[0]->type_after = strdup(">>");
		else if (line[0][i] == '<' && line[0][i + 1] == '<')
			node[0]->type_after = strdup("<<");
	}
	else
	{
		// node[0]->type_after = calloc(1, 2);
		node[0]->type_after = malloc(sizeof(char) * 2);
		node[0]->type_after[0] = line[0][i];
		node[0]->type_after[1] = '\0';
	}
}
t_node *	order_nodes(t_node **current_node)
{
	/*
		node1 -> node2 -> node3 -> ...etc
		Example:- node2:
		< text1 < text2 < text3 echo hi < text4
		it will come like this:
		< text1
		< text2
		< text3
		< text4 echo hi
	*/
	char	**args;
	char	*str_cmd;
	char	*space;
	t_node	*file_nodes;
	t_node	*first_node;
	// t_node	*node;

	file_nodes = NULL;
	first_node = NULL;
	args = current_node[0]->args;
	space = " ";
	str_cmd = NULL;
	while (*args)
	{
		// make new node of files
		if (is_operator_fun(*args) == 1)
		{
			if (file_nodes)
			{
				file_nodes->type_after = strdup(args);
				file_nodes = file_nodes->next;
			}
			file_nodes = malloc(sizeof(t_node));
			if (!file_nodes)
				return ;
			if (!first_node)
				first_node = file_nodes;
			file_nodes->type_before = strdup(args);
			args++;
			file_nodes->args = ft_split(args, ' ');
		}
		else
		{
			// strjoin the command
			if (str_cmd)
				str_cmd = ft_restore_value(&str_cmd, ft_strjoin(str_cmd, space), 1);
			str_cmd = ft_restore_value(&str_cmd, ft_strjoin(str_cmd, args), 1);
		}
		args++;
	}
	// marge last node with the commands
	file_nodes->args = marge_2_splits(file_nodes->args, ft_split(str_cmd, ' '));
	str_cmd = free_char(str_cmd);
	// replace and free current node
	free_nodes(current_node);
	return (first_node);
}

char	*insert_node(t_node **node, char **line, int i, int j)
{
	char	*cmd_order;
	char	*before_tybe;
	int		x;

	x = 0;
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
void	order_info_nodes(t_info *info)
{
	t_node *current_node;

	current_node = info->first_node;
	while (current_node)
	{
		current_node = order_nodes(&current_node);
		current_node = current_node->next;
	}
	
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;
	char	*before_tybe;
	int		i;
	int		j;

	j = 0;
	i = 0;
	node = malloc(sizeof(t_node));
	if (!node)
	{
		info->first_node = NULL;
		return ;
	}
	node->type_before = strdup("start");
	info->first_node = node;
	node->last_fd_name = NULL;
	while (line[i])
	{
		if (line[i] == '|')
		{
			type_after_fun(&node, &line, i);
			before_tybe = insert_node(&node, &line, i, j);
			dir_bilt_fun(&node, before_tybe);
			j = i;
			node->next = NULL;
			node = node->next;
			node = malloc(sizeof(t_node));
			node->type_before = strdup(before_tybe);
		}
		i++;
	}
	node->type_after = strdup("end");
	before_tybe = insert_node(&node, &line, i, j);
	dir_bilt_fun(&node, before_tybe);
	node->next = NULL;
	order_info_nodes(info);
}
