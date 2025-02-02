
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
