
#include "../minishell.h"

void	free_nodes(t_node **nodes)
{
	t_node	*temp;

	while (*nodes)
	{
		temp = *nodes;
		*nodes = (*nodes)->next;
		if (temp->args)
		{
			for (int i = 0; temp->args[i]; i++)
				free(temp->args[i]);
			free(temp->args);
		}
		free(temp->type_before);
		free(temp->type_after);
		free(temp);
	}
}
void	free_node(t_node **nodes)
{

	int	i;

	i = 0;
	if (nodes[0]->args)
	{
		while (nodes[0]->args[i])
		{
			free(nodes[0]->args[i]);
			nodes[0]->args[i] = NULL;
			i++;
		}
		free(nodes[0]->args);
		nodes[0]->args = NULL;
	}
	nodes[0]->type_before = free_char(&(nodes[0]->type_before));
	nodes[0]->type_after = free_char(&(nodes[0]->type_after));
	nodes[0]->last_fd_name = free_char(&(nodes[0]->last_fd_name));
	nodes[0]->next = NULL;
	free(*nodes);
	*nodes = NULL;
}
