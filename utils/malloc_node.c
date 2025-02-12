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

void	copy_node(t_node *to_node, t_node *from_node, int is_free_before)
{
	if (!from_node)
	{
		printf("\n\n--------------  Error  --------------\n\n");
		return ;
	}
	if (is_free_before == 1 && to_node->type_after)
		to_node->type_after = free_char(&to_node->type_after);
	if (is_free_before == 1 && to_node->type_before)
		to_node->type_before = free_char(&to_node->type_before);
	if (is_free_before == 1 && to_node->last_fd_name)
		to_node->last_fd_name = free_char(&to_node->last_fd_name);
	if (is_free_before == 1 && to_node->args)
		free_split(to_node->args, len_split(to_node->args));
	
	to_node->type_after = ft_strdup(from_node->type_after);
	to_node->type_before = ft_strdup(from_node->type_before);
	to_node->last_fd_name = ft_strdup(from_node->last_fd_name);
	to_node->fd_file = from_node->fd_file;
	to_node->is_dir_bilt_cmd = from_node->is_dir_bilt_cmd;
	to_node->next = from_node->next;
	to_node->args = copy_split(from_node->args);
}
