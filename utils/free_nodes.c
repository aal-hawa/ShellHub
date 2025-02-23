
#include "../minishell.h"

// void	free_nodes(t_node **nodes)
// {
// 	t_node	*temp;

// 	while (*nodes)
// 	{
// 		temp = *nodes;
// 		*nodes = (*nodes)->next;
// 		if (temp->args)
// 		{
// 			for (int i = 0; temp->args[i]; i++)
// 				free(temp->args[i]);
// 			free(temp->args);
// 		}
// 		free(temp->type_before);
// 		free(temp->type_after);
// 		free(temp);
// 	}
// }
void	free_node(t_node **node)
{
	if (!node || !*node)
		return ;
	if (node[0]->args)
		free_array2d(&(node[0]->args), 0);
	node[0]->type_before = free_char(&(node[0]->type_before));
	node[0]->type_after = free_char(&(node[0]->type_after));
	node[0]->last_fd_name = free_char(&(node[0]->last_fd_name));
	node[0]->next = NULL;
	free(*node);
	*node = NULL;
}
