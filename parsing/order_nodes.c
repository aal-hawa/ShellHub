# include "../minishell.h"

t_node *	order_nodes(t_node **current_node, t_info *info)
{
	char	**args;
	char	*str_cmd;
	char	*str_join;
	int		i;
	t_node	*nodes_input;
	t_node	*nodes_output;
	t_node	*first_input;
	t_node	*first_output;

	nodes_input = NULL;
	nodes_output = NULL;
	first_input = NULL;
	args = current_node[0]->args;
	str_cmd = NULL;
	nodes_input = malloc_node();
	nodes_output = malloc_node();
	if (!nodes_input || !nodes_output)
		return (*current_node);
	first_input = nodes_input;
	first_output = nodes_output;
	i = 0;
	while (args[i])
	{
		// make new node of files
		if (is_operator_fun(args[i]) == 1)
		{
			if (is_operator_input_fun(args[i]) && nodes_input->args)
			{
				nodes_input->type_after = ft_strdup(args[i]);
				dir_bilt_fun(&nodes_input, nodes_input->type_before, info);
				nodes_input->next = malloc_node();
				nodes_input = nodes_input->next;
			}
			else if (is_operator_output_fun(args[i]) && nodes_output->args)
			{
				nodes_output->type_after = ft_strdup(args[i]);
				dir_bilt_fun(&nodes_output, nodes_output->type_before, info);
				nodes_output->next = malloc_node();
				nodes_output = nodes_output->next;
			}
			if (is_operator_input_fun(args[i]))
			{
				nodes_input->type_before = ft_strdup(args[i]);
				i++;
				nodes_input->args = ft_split(args[i], ' ');
			}
			else if (is_operator_output_fun(args[i]))
			{
				nodes_output->type_before = ft_strdup(args[i]);
				i++;
				nodes_output->args = ft_split(args[i], ' ');
			}
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
			if (first_output->type_before)
				nodes_input->type_after = ft_strdup(first_output->type_before);
			else
				nodes_input->type_after = ft_strdup("end");
			if (nodes_input->args)
				dir_bilt_fun(&nodes_input, nodes_input->type_before, info);
		}
		if (!args[i] && !current_node[0]->next && nodes_output->args)
		{
			nodes_output->type_after = ft_strdup("end");
			if (nodes_output->args)
				dir_bilt_fun(&nodes_output, nodes_output->type_before, info);
		}
	}
	// marge last node with the commands
	nodes_input->args = marge_2_splits(nodes_input->args, ft_split(str_cmd, ' '));
	str_cmd = free_char(&str_cmd);
	// replace and free current node
	if (!first_input->type_after)
	first_input->type_after = ft_strdup(current_node[0]->type_after);
	if (!first_input->type_before)
	first_input->type_before = ft_strdup(current_node[0]->type_before);
	if (first_input->is_dir_bilt_cmd == -1)
	first_input->is_dir_bilt_cmd = current_node[0]->is_dir_bilt_cmd;
	if (!first_output->args)
		free_node(&first_output);
	else
		nodes_input->next = first_output;
	// free_node(current_node);
	return (first_input);
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
