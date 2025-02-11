#include "../minishell.h"

void	dir_bilt_fun(t_node **node, char *before_tybe, t_info *info)
{
	if (!ft_strcmp(before_tybe, "<") || !ft_strcmp(before_tybe,"<<")
	 || !ft_strcmp(before_tybe,">") || !ft_strcmp(before_tybe,">>"))
		node[0]->is_dir_bilt_cmd = 0;
	else if (!ft_strcmp(node[0]->args[0], "cd")
		|| !ft_strcmp(node[0]->args[0], "pwd") 
		|| !ft_strcmp(node[0]->args[0], "echo")
		|| !ft_strcmp(node[0]->args[0], "env") 
		|| !ft_strcmp(node[0]->args[0], "export")
		||!ft_strcmp(node[0]->args[0], "unset")
		|| !ft_strcmp(node[0]->args[0], "exit"))
		node[0]->is_dir_bilt_cmd = 1;
	else
	{
		node[0]->is_dir_bilt_cmd = 2;
		info->str_i++;
	}
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
t_node *	order_nodes(t_node **current_node)
{
	char	**args;
	char	*str_cmd;
	char	*space;
	char	*str_join;
	t_node	*file_nodes;
	t_node	*first_node;

	file_nodes = NULL;
	first_node = NULL;
	args = current_node[0]->args;
	space = " ";
	str_cmd = NULL;
	file_nodes = malloc_node();
	if (!file_nodes)
		return (*current_node);
	first_node = file_nodes;
		

	while (*args)
	{
		// make new node of files
		if (is_operator_fun(*args) == 1)
		{
			if (file_nodes->args)
			{
				file_nodes->type_after = ft_strdup(*args);
				file_nodes->next = malloc_node();
				file_nodes = file_nodes->next;
			}
			file_nodes->type_before = ft_strdup(*args);
			args++;
			file_nodes->args = ft_split(*args, ' ');

		}
		else
		{
			if (str_cmd)
			{
				str_join =  ft_strjoin(str_cmd, space);
				str_cmd = ft_restore_value(&str_cmd, &str_join, 1);
			}
			str_join =  ft_strjoin(str_cmd, *args);
			str_cmd = ft_restore_value(&str_cmd, &str_join, 1);
		}
		if (args)
			args++;
	}
	// marge last node with the commands
	file_nodes->args = marge_2_splits(file_nodes->args, ft_split(str_cmd, ' '));

	str_cmd = free_char(&str_cmd);
	// replace and free current node
	if (!first_node->type_after)
		first_node->type_after = ft_strdup(current_node[0]->type_after);
	if (!first_node->type_before)
		first_node->type_before = ft_strdup(current_node[0]->type_before);
	if (first_node->is_dir_bilt_cmd == -1)
		first_node->is_dir_bilt_cmd = current_node[0]->is_dir_bilt_cmd;
	free_nodes(current_node);
	return (first_node);
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
void	order_info_nodes(t_info *info)
{
	t_node *current_node;
	t_node *first_node;
	t_node *next_node;

	current_node = malloc_node();
	copy_node(current_node, info->first_node, 0);
	// current_node = info->first_node;
	first_node = NULL;
	next_node = NULL;
	if (current_node)
		next_node = current_node->next;
	while (current_node)
	{
		current_node = order_nodes(&current_node);
		if (!first_node)
			first_node = current_node;
		while (current_node)
			current_node = current_node->next;
		current_node = next_node;
		if (current_node)
			next_node = current_node->next;
	}
	printf("FINISH WHILE: order_info_nodes\n");
	info->first_node = first_node;
}

void	create_nodes(char *line, t_info *info)
{
	t_node	*node;
	char	*before_tybe;
	int		i;
	int		j;


	j = 0;
	i = 0;
	node = malloc_node();
	if (!node)
	{
		info->first_node = NULL;
		return ;
	}
	node->type_before = ft_strdup("start");
	info->first_node = node;
	node->last_fd_name = NULL;
	while (line[i])
	{
		if (line[i] == '|')
		{
			type_after_fun(&node, &line, i);
			printf("FINISH: type_after_fun\n");
			before_tybe = insert_node(&node, &line, i, j);
			printf("FINISH: insert_node\n");

			dir_bilt_fun(&node, before_tybe, info);
			printf("FINISH: dir_bilt_fun\n");

			j = i;
			// node->next = NULL;
			node->next = malloc_node();
			node = node->next;
			node->type_before = ft_strdup(before_tybe);
			printf("FINISH: -------------------\n");
		}
		i++;
	}
	node->type_after = ft_strdup("end");
	before_tybe = insert_node(&node, &line, i, j);
	dir_bilt_fun(&node, before_tybe, info);
	node->next = NULL;

	// print_nodes(info->first_node);
	// printf("---------------FINISH: print_nodes-----------------\n");
	order_info_nodes(info);
	print_nodes(info->first_node);
	printf("---------------FINISH: order_info_nodes-----------------\n");
	printf("FINISH: order_info_nodes\n");

	printf("info->first_node->is_dir_bilt_cmd %d\n",info->first_node->is_dir_bilt_cmd);
	printf("info->first_node->type_after %s\n",info->first_node->type_after);
	printf("info->first_node->type_before %s\n",info->first_node->type_before);
	printf("info->first_node->args[0] %s\n",info->first_node->args[0]);
}
