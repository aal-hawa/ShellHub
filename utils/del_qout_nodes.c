#include "../minishell.h"

void	del_qout_nodes(t_node *node)
{
	int	i;
	char	*new_args;

	i = 0;
	while (node)
	{
		i = 0;
		while(node->args && node->args[i])
		{
			if (node->args[i][0] == '\'' || node->args[i][0] == '\"')
			{
				new_args = ft_strccpy(&node->args[i][1],node->args[i][0]);
				ft_restore_value(&node->args[i], &new_args, 1);
			}
			i++;
		}
		node = node->next;
	}
}
