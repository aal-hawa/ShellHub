# include "../minishell.h"

int	init_node_order(t_node_order *node_order, t_node **current_node)
{
	node_order->nodes_input = NULL;
	node_order->nodes_output = NULL;
	node_order->first_input = NULL;
	node_order->args = current_node[0]->args;
	node_order->str_cmd = NULL;
	node_order->nodes_input = malloc_node();
	node_order->nodes_output = malloc_node();
	if (!node_order->nodes_input || !node_order->nodes_output)
		return (0);
	node_order->first_input = node_order->nodes_input;
	node_order->first_output = node_order->nodes_output;
	node_order->i = 0;
	return (1);
}
void	last_order_nodes(t_node_order *node_order, t_node **current_node, t_info *info)
{
	if (!node_order->args[node_order->i] && !current_node[0]->next)
	{
		if (node_order->first_output->type_before)
			node_order->nodes_input->type_after = ft_strdup(node_order->first_output->type_before);
		else
			node_order->nodes_input->type_after = ft_strdup("end");
		if (node_order->nodes_output->args)
		{
			dir_bilt_fun(&node_order->nodes_input, node_order->nodes_input->type_before, info);
			node_order->nodes_output->type_after = ft_strdup("end");
			if (node_order->nodes_output->args)
				dir_bilt_fun(&node_order->nodes_output, node_order->nodes_output->type_before, info);
		}
	}
}

void	do_operator(t_node_order *node_order, t_node **nodes, t_info *info)
{
	if (nodes[0]->args)
	{
		nodes[0]->type_after = ft_strdup(node_order->args[node_order->i]);
		dir_bilt_fun(&nodes[0], nodes[0]->type_before, info);
		nodes[0]->next = malloc_node();
		nodes[0] = nodes[0]->next;
	}
	nodes[0]->type_before = ft_strdup(node_order->args[node_order->i]);
	node_order->i++;
	nodes[0]->args = ft_split(node_order->args[node_order->i], ' ');
}

void	make_order_nodes(t_node_order *node_order,t_node **current_node, t_info *info)
{
	while (node_order->args[node_order->i])
	{
		if (is_operator_fun(node_order->args[node_order->i]) == 1)
		{
			if (is_operator_input_fun(node_order->args[node_order->i]))
				do_operator(node_order, &(node_order->nodes_input), info);
			else if (is_operator_output_fun(node_order->args[node_order->i]))
				do_operator(node_order, &(node_order->nodes_output), info);
		}
		else
		{
			if (node_order->str_cmd)
			{
				node_order->str_join =  ft_strjoin(node_order->str_cmd, " ");
				node_order->str_cmd = ft_restore_value(&node_order->str_cmd, &node_order->str_join, 1);
			}
			node_order->str_join =  ft_strjoin(node_order->str_cmd, node_order->args[node_order->i]);
			node_order->str_cmd = ft_restore_value(&node_order->str_cmd, &node_order->str_join, 1);
		}
		if (node_order->args[node_order->i])
			node_order->i++;
	}
	last_order_nodes(node_order, current_node, info);
}

t_node *	order_nodes(t_node **current_node, t_info *info)
{
	t_node_order	node_order;

	if (!init_node_order(&node_order, current_node))
		return (*current_node);
	make_order_nodes(&node_order, current_node, info);
	// marge last node with the commands
	node_order.nodes_input->args = marge_2_splits(node_order.nodes_input->args, ft_split(node_order.str_cmd, ' '));
	node_order.str_cmd = free_char(&node_order.str_cmd);
	// replace and free current node
	if (!node_order.first_input->type_after)
		node_order.first_input->type_after = ft_strdup(current_node[0]->type_after);
	if (!node_order.first_input->type_before)
		node_order.first_input->type_before = ft_strdup(current_node[0]->type_before);
	if (node_order.first_input->is_dir_bilt_cmd == -1)
		node_order.first_input->is_dir_bilt_cmd = current_node[0]->is_dir_bilt_cmd;
	if (!node_order.first_output->args)
		free_node(&node_order.first_output);
	else
		node_order.nodes_input->next = node_order.first_output;
	// free_node(current_node);
	return (node_order.first_input);
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
