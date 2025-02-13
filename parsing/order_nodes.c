# include "../minishell.h"

t_node *	order_nodes(t_node **current_node, t_info *info)
{
	char	**args;
	char	*str_cmd;
	char	*str_join;
	int		i;
	t_node	*file_nodes;
	t_node	*first_node;

	file_nodes = NULL;
	first_node = NULL;
	args = current_node[0]->args;
	str_cmd = NULL;
	file_nodes = malloc_node();
	if (!file_nodes)
		return (*current_node);
	first_node = file_nodes;
	i = 0;
	while (args[i])
	{
		// make new node of files
		if (is_operator_fun(args[i]) == 1)
		{
			if (file_nodes->args)
			{
				file_nodes->type_after = ft_strdup(args[i]);
				dir_bilt_fun(&file_nodes, file_nodes->type_before, info);
				file_nodes->next = malloc_node();
				file_nodes = file_nodes->next;
			}
			file_nodes->type_before = ft_strdup(args[i]);
			i++;
			file_nodes->args = ft_split(args[i], ' ');
		}
		else
		{
			if (str_cmd)
			{
				str_join =  ft_strjoin(str_cmd, " ");
				str_cmd = ft_restore_value(&str_cmd, &str_join, 1);
			}
			str_join =  ft_strjoin(str_cmd, args[i]);
			str_cmd = ft_restore_value(&str_cmd, &str_join, 1);
		}
		if (args[i])
			i++;
		if (!args[i] && !current_node[0]->next)
		{
			file_nodes->type_after = ft_strdup("end");
			if (file_nodes->args)
				dir_bilt_fun(&file_nodes, file_nodes->type_before, info);
		}
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
	// free_node(current_node);
	return (first_node);
}

void	order_info_nodes(t_info *info)
{
	t_node *current_node;
	t_node *first_node;
	t_node *next_node;

	current_node = malloc_node();
	copy_node(&current_node, &info->first_node, 0);
	first_node = NULL;
	next_node = NULL;
	if (current_node)
		next_node = current_node->next;
	while (current_node)
	{
		current_node = order_nodes(&current_node, info);
		if (!first_node)
			first_node = current_node;
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = next_node;
		current_node = current_node->next;
		if (current_node)
			next_node = current_node->next;
	}
	free_node(&info->first_node);
	info->first_node = NULL;
	info->first_node = first_node;
}
