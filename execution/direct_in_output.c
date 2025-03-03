# include "../minishell.h"

int	utils_direct_fun(t_node *node, t_info *info)
{
	int	is_exit;

	is_exit = 0;
	if (info->fd_file_w == -1 || info->fd_file_r == -1)
	{
		info->status_exit = 1;
		// info->is_exit_one = 1;
		info->fd_file_w = close_fd_fun(info->fd_file_w);
		info->fd_file_r = close_fd_fun(info->fd_file_r);
		info->fd_file_w = -2;
		info->fd_file_r = -2;
		is_exit = 1;
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
		if (node->next)
			node->next->is_no_inpipe = 1;
	}
	return (is_exit);
}

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
		open_here_doc(node, info);
	return (utils_direct_fun(node, info));
}
