# include "../minishell.h"

int	init_node_order(t_node_order *node_order, t_node **current_node)
{
	node_order->nodes_input = NULL;
	node_order->nodes_output = NULL;
	node_order->first_input = NULL;
	node_order->args = current_node[0]->args;
	node_order->str_cmd = NULL;
	node_order->nodes_input = malloc_node2();
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
		nodes[0]->next = malloc_node();
		nodes[0] = nodes[0]->next;
	}
	nodes[0]->type_before = ft_strdup(node_order->args[node_order->i]);
	node_order->i++;
	nodes[0]->args = ft_split(node_order->args[node_order->i], ' ');
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

void	order_nodes(t_node **current_node, t_token **token)
{
	t_node_order	node_order;
	char			**array2d;

	if (!init_node_order(&node_order, current_node))
		return ;
	make_order_nodes(&node_order);
	array2d = ft_split(node_order.str_cmd, ' ');
	token[0]->cmd = array2d;
	if (token[0]->cmd && is_biult_fun(token[0]->cmd[0]) == 0)
		token[0]->is_bilt_cmd = 1;
	if (!node_order.first_input->args)
		free_nodes(&(node_order.first_input));
	if (!node_order.first_output->args)
		free_nodes(&(node_order.first_output));
	token[0]->input_redirect = node_order.first_input;
	token[0]->output_redirect = node_order.first_output;
	node_order.str_cmd = free_string(&node_order.str_cmd);
}

void	order_info_nodes(t_info *info, t_node **node)
{
	t_node *next_node;
	t_token *tokens;

	tokens = malloc_token();
	info->tokens = tokens;
	next_node = NULL;
	if (*node)
		next_node = *node;
	print_array2d(next_node->args, 1);
	while (next_node)
	{
		order_nodes(&next_node, &tokens);
		del_qout_nodes(tokens->input_redirect);
		del_qout_nodes(tokens->output_redirect);
		del_qout_cmd(tokens->cmd);
		next_node = next_node->next;
		if (next_node)
		{
			tokens->next = malloc_token();
			tokens = tokens->next;
		}
	}
}
