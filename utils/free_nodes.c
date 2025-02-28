
#include "../minishell.h"

void	free_nodes(t_node **node)
{
	t_node	*temp;

	if (!node || !*node)
			return ;
	while (node[0])
	{
		if (node[0]->args)
			free_array2d(&(node[0]->args), 0);
		if (node[0]->result_builtins)
			free_array2d(&(node[0]->result_builtins), 0);
		if (node[0]->type_before)
			node[0]->type_before = free_string(&(node[0]->type_before));
		if (node[0]->type_after)
			node[0]->type_after = free_string(&(node[0]->type_after));
		if (node[0]->fd_name)
			node[0]->fd_name = free_string(&(node[0]->fd_name));
		// node[0]->next = NULL;
		temp = node[0];
		node[0] = node[0]->next;
		free(temp);
	}
}
void	free_node(t_node **node)
{
	if (!node || !node[0])
		return ;
	if (node[0]->args)
		free_array2d(&(node[0]->args), 0);
	if (node[0]->result_builtins)
		free_array2d(&(node[0]->result_builtins), 0);
	if (node[0]->type_before)
		node[0]->type_before = free_string(&(node[0]->type_before));
	if (node[0]->type_after)
		node[0]->type_after = free_string(&(node[0]->type_after));
	if (node[0]->fd_name)
		node[0]->fd_name = free_string(&(node[0]->fd_name));
	// node[0]->next = NULL;
	free(*node);
	*node = NULL;
}
