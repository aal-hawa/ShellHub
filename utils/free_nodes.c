
#include "../minishell.h"

void	free_nodes(t_node **node)
{
	t_node	*temp;
	return ;
	if (!node || !*node)
			return ;
	while (*node)
	{
		temp = node[0]->next;
		if (node[0]->args)
			free_array2d(&(node[0]->args), 0);
		if (node[0]->result_builtins)
			free_array2d(&(node[0]->result_builtins), 0);
		node[0]->type_before = free_string(&(node[0]->type_before));
		node[0]->type_after = free_string(&(node[0]->type_after));
		node[0]->last_fd_name = free_string(&(node[0]->last_fd_name));
		node[0]->next = NULL;
		free(*node);
		*node = NULL;
		*node = temp;
	}
}
void	free_node(t_node **node)
{
	if (!node || !*node)
		return ;
	if (node[0]->args)
		free_array2d(&(node[0]->args), 0);
	if (node[0]->result_builtins)
		free_array2d(&(node[0]->result_builtins), 0);
	node[0]->type_before = free_string(&(node[0]->type_before));
	node[0]->type_after = free_string(&(node[0]->type_after));
	node[0]->last_fd_name = free_string(&(node[0]->last_fd_name));
	node[0]->next = NULL;
	free(*node);
	*node = NULL;
}
