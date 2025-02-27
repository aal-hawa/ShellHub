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
	{
		if (node_order->nodes_input)
			free_node(&node_order->nodes_input);
		if (node_order->nodes_output)
			free_node(&node_order->nodes_output);
		return (0);
	}
	node_order->first_input = node_order->nodes_input;
	node_order->first_output = node_order->nodes_output;
	node_order->i = 0;
	return (1);
}

void	do_operator(t_node_order *node_order, t_node **nodes)
{
	if (nodes[0]->args)
	{
		nodes[0]->type_after = ft_strdup(node_order->args[node_order->i]);
		dir_bilt_fun(&nodes[0]);
		nodes[0]->next = malloc_node();
		nodes[0] = nodes[0]->next;
	}
	nodes[0]->type_before = ft_strdup(node_order->args[node_order->i]);
	node_order->i++;
	nodes[0]->args = ft_split(node_order->args[node_order->i], ' ');
}

void	last_order_nodes(t_node_order *node_order, t_node **current_node)
{
	if (!node_order->args[node_order->i] && !current_node[0]->next)
	{
		
		if (node_order->first_output->type_before)
			node_order->nodes_input->type_after =
			ft_strdup(node_order->first_output->type_before);
		else
			node_order->nodes_input->type_after = ft_strdup("end");
		if (node_order->nodes_output->args)
		{
			if (node_order->nodes_input->type_before)
				dir_bilt_fun(&node_order->nodes_input);
			node_order->nodes_output->type_after = ft_strdup("end");
			if (node_order->nodes_output->args
				&& node_order->nodes_output->type_before)
				dir_bilt_fun(&node_order->nodes_output);
		}
	}
}

void	make_order_nodes(t_node_order *node_order)
{
	while (node_order->args[node_order->i])
	{
		if (is_operator_fun(node_order->args[node_order->i]) > 0)
		{
			if (is_operator_input_fun(node_order->args[node_order->i]))
				do_operator(node_order, &(node_order->nodes_input));
			else if (is_operator_output_fun(node_order->args[node_order->i]))
				do_operator(node_order, &(node_order->nodes_output));
		}
		else
		{
			if (node_order->str_cmd)
			{
				node_order->str_join = ft_strjoin(node_order->str_cmd, " ");
				node_order->str_cmd = ft_restore_value(&node_order->str_cmd,
				&node_order->str_join, 1);
			}
			node_order->str_join = ft_strjoin(node_order->str_cmd,
				node_order->args[node_order->i]);
			node_order->str_cmd = ft_restore_value(&node_order->str_cmd,
				&node_order->str_join, 1);
		}
		if (node_order->args[node_order->i])
			node_order->i++;
	}
}

void	chng_defult_frst_inpt_vlu(t_node_order *node_order,
		t_node **current_node)
{
	if (!node_order->first_input->type_after)
	{
		if (node_order->first_output->type_before)
			node_order->first_input->type_after =
			ft_strdup(node_order->first_output->type_before);
		else
			node_order->first_input->type_after =
			ft_strdup(current_node[0]->type_after);
	}
	if (!node_order->first_input->type_before)
		node_order->first_input->type_before =
		ft_strdup(current_node[0]->type_before);
	if (node_order->first_input->is_dir_bilt_cmd == -1
		&& node_order->first_input->type_before)
		dir_bilt_fun(&node_order->first_input);
}

void	chng_defult_node_vlu(t_node_order *node_order, t_node **current_node)
{
	if (!node_order->nodes_output->type_after)
		node_order->nodes_output->type_after = ft_strdup(current_node[0]->type_after);
	if (node_order->nodes_output && node_order->nodes_output->type_before && node_order->nodes_output->is_dir_bilt_cmd == -1)
		dir_bilt_fun(&(node_order->nodes_output));
	if (!node_order->nodes_input->type_after)
	{
		if (node_order->first_output->type_before)
			node_order->nodes_input->type_after = ft_strdup(node_order->first_output->type_before);
		else
			node_order->nodes_input->type_after = ft_strdup(current_node[0]->type_after);
	}
	if (node_order->nodes_input && node_order->nodes_input->type_before && node_order->nodes_input->is_dir_bilt_cmd == -1)
		dir_bilt_fun(&(node_order->nodes_input));
}

void	order_nodes(t_node **to_node, t_node **current_node)
{
	t_node_order	node_order;
	char			**array2d;

	if (!init_node_order(&node_order, current_node))
		return ;
	make_order_nodes(&node_order);
	last_order_nodes(&node_order, current_node);
	array2d = ft_split(node_order.str_cmd, ' ');
	node_order.nodes_input->args = marge_2_splits(node_order.nodes_input->args,
		array2d);
	free_array2d(&array2d, 0);
	node_order.str_cmd = free_string(&node_order.str_cmd);
	chng_defult_frst_inpt_vlu(&node_order, current_node);
	chng_defult_node_vlu(&node_order, current_node);
	if (!node_order.first_output->args)
		free_node(&node_order.first_output);
	else
		node_order.nodes_input->next = node_order.first_output;
	if (!to_node[0]->args)
	{
		free_node(to_node);
		to_node[0] = node_order.first_input;
	}
	else
		to_node[0]->next = node_order.first_input;
}

void	order_info_nodes(t_info *info)
{
	t_node *current_node;
	t_node *first_node;
	t_node *next_node;

	current_node = malloc_node();
	first_node = NULL;
	next_node = NULL;
	if (info->first_node)
		next_node = info->first_node;
	while (next_node)
	{
		order_nodes(&current_node, &next_node);
		del_qout_nodes(current_node);
		if (!first_node)
			first_node = current_node;
		while (current_node->next)
			current_node = current_node->next;
		if (next_node)
			next_node = next_node->next;
	}
	free_node(&info->first_node);
	info->first_node = NULL;
	info->first_node = first_node;
}
