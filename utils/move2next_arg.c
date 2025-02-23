#include "../minishell.h"

char	**move2next_arg(t_node **cmd_node)
{
	char	**new_args;

	new_args = copy_split(cmd_node[0]->args + 1);
	free_array2d(&cmd_node[0]->args, 0);
	if (!new_args)
		return (NULL);
	cmd_node[0]->args = new_args;
	return (new_args);
}
