# include "../minishell.h"

int	direct_fun(t_node *node, t_info *info)
{
	if (!ft_strcmp(node->type_before,">"))
	{
		info->fd_file_w = open_file_w(node->args[0]);
		info->is_for_w = 1;
		node->fd_file = info->fd_file_w;
		if (!node->next)
			node->is_do_execute = 1;
	}
	else if (!ft_strcmp(node->type_before,">>"))
	{
		info->fd_file_w = open_file_w_b(node->args[0]);
		info->is_for_w = 1;
		node->fd_file = info->fd_file_w;
	}
	else if (!ft_strcmp(node->type_before, "<"))
		init_files(node, info);
	else if (!ft_strcmp(node->type_before, "<<"))
		init_here_doc(node, info);
	if (info->fd_file_w == -1 || info->fd_file_r == -1)
	{
		info->status_exit = 1;
		info->is_exit_one = 1;
		// return (1);
	}
	else
		info->status_exit = 0;
	if (node->args[1])
	{
		if (is_biult_fun(node->args[1]) == 1)
			node->is_do_execute = -1;
		else
			node->is_do_execute = 1;
	}
	else if (is_operator_fun(node->type_after) == 2 && info->fd_file_r >= 0)
	{
		info->fd_file_r = close_fd_fun(info->fd_file_r);
		// node->next->is_do_execute = 3;
		// node->is_do_execute = 2;
	}
	return (0);
}
