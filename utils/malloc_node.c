#include "../minishell.h"

t_node	*malloc_node()
{
	t_node	*node;
	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->fd_file = -1;
	node->is_dir_bilt_cmd = -1;
	node->last_fd_name = NULL;
	node->next = NULL;
	node->type_after = NULL;
	node->type_before = NULL;
	return (node);
}