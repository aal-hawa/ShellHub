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
	node->is_do_execute = 0;
	return (node);
}

void	copy_node(t_node **to_node, t_node **from_node, int is_free_before)
{
	if (!from_node[0])
	{
		printf("\n\n--------------  Error  --------------\n\n");
		return ;
	}
	if (is_free_before == 1 && to_node[0]->type_after)
		to_node[0]->type_after = free_char(&to_node[0]->type_after);
	if (is_free_before == 1 && to_node[0]->type_before)
		to_node[0]->type_before = free_char(&to_node[0]->type_before);
	if (is_free_before == 1 && to_node[0]->last_fd_name)
		to_node[0]->last_fd_name = free_char(&to_node[0]->last_fd_name);
	if (is_free_before == 1 && to_node[0]->args)
		free_split(to_node[0]->args, len_split(to_node[0]->args));
	
	to_node[0]->type_after = ft_strdup(from_node[0]->type_after);
	to_node[0]->type_before = ft_strdup(from_node[0]->type_before);
	to_node[0]->last_fd_name = ft_strdup(from_node[0]->last_fd_name);
	to_node[0]->fd_file = from_node[0]->fd_file;
	to_node[0]->is_dir_bilt_cmd = from_node[0]->is_dir_bilt_cmd;
	to_node[0]->is_do_execute = from_node[0]->is_do_execute;
	to_node[0]->next = from_node[0]->next;
	to_node[0]->args = copy_split(from_node[0]->args);
}
