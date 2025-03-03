# include "../minishell.h"

void	str_i_count(t_info *info)
{
	t_node	*node;

	node = info->first_node;
	while (node)
	{
		if (!ft_strcmp(node->type_after, "|"))
			info->str_i++;
		node = node->next;
	}
	if (info->str_i > 0)
		info->str_i++;
	else if (info->str_i == 0)
	{
		node = info->first_node;
		while (node)
		{
			if (node->is_dir_bilt_cmd == 2
				||(node->is_dir_bilt_cmd == 0
				&& len_split(node->args) > 1
				&& !is_biult_fun(node->args[1])))
				info->str_i++;
			node = node->next;
		}
	}
	// printf ("info->str_i: %d\n", info->str_i);
}
void	do_builtins_check_fork(t_node *node,  t_info *info, char ***result_blts, t_node **cmd_node)
{
	pid_t	frs_1;
	if (info->str_i > 0)
	{
		frs_1 = fork();
		if (frs_1 == 0)
		{
			do_builtins(node, result_blts, info);
			if (info->is_builtins_file == 1)
			{
				info->is_builtins_file = 0;
				print_array2d_fd(*result_blts, info->fd_file_w);
			}
			else
			{
				dup2(info->fds[info->i_childs + 1][1], STDOUT_FILENO);
				print_array2d_fd(*result_blts, info->fds[info->i_childs + 1][1]);
				// for_execve(node, info->fds, info->frs, info, *result_blts, &node->next);
			}
			close_fds_childs(info->fds, info);
			close(info->fds[info->i_childs + 1][1]);
			close(info->fds[info->i_childs][0]);
			if (info->str_i > 0)
				de_allocate(&info->fds, &info->frs, info->str_i);
			free_array2d(result_blts, 0);
			exit_number(info->status_exit, info);
		}
		if (!cmd_node[0])
		cmd_node[0] = node;
		cmd_node[0] = cmd_node[0]->next;
		info->i_childs++;
	}
	else
		do_builtins(node, result_blts, info);
}

int open_all_files(t_node *node, t_info *info)
{
	t_node	*this_node;

	this_node = node;
	while (this_node && ft_strcmp(this_node->type_before, "|"))
	{
		if(direct_fun(this_node, info) == 1)
			return (1);
		this_node = this_node->next;
	}
	info->is_open_files = 0;
	return (0);
}
void	next_cmd(t_node **node, t_info *info)
{
	// int	i;

	// i = 0;
	while (node[0] && ft_strcmp(node[0]->type_after, "|"))
	{
		// i++;
		node[0] = node[0]->next;
	}
	if (node[0] && !ft_strcmp(node[0]->type_after, "|"))
	{
		// close(info->fds[i][0]);
		// close(info->fds[i][1]);
		node[0] = node[0]->next;
		info->is_open_files = 1;
	}

}

int	check_open_files(t_node **node, t_info *info)
{
	int		is_exit;
	
	is_exit = 0;
	if (info->is_open_files == 1)
	is_exit = open_all_files(*node, info);
	if (!ft_strcmp(node[0]->type_after, "|"))
		info->is_open_files = 1;
	if (is_exit == 1)
	{
		next_cmd(node, info);
		return (1);
	}
	return (0);
}

void	dir_blt_execve_fun(t_node *node, int **fds, pid_t *frs, t_info *info)
{
	char	**result_blts;
	t_node	*cmd_node;

	cmd_node = NULL;
	result_blts = NULL;
	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (node)
	{
		if (check_open_files(&node, info) == 1)
			continue ;
		info->is_for_w = 0;
		if (node->is_dir_bilt_cmd == 1)
			do_builtins_check_fork(node, info, &result_blts, &cmd_node);
		if (!is_can_do_execve(&node, &cmd_node, info))
			continue ;
		for_execve(node, fds, frs, info, result_blts, &cmd_node);
		if (node)
			node = node->next;
	}
	if (result_blts)
		free_array2d(&result_blts, 0);
}

void	open_herdoc_files(t_node *node, t_info *info)
{
	while (node)
	{
		if (!ft_strcmp(node->type_before, "<<"))
		{
			init_here_doc(node, info);
		}
		node = node->next;
	}
}

int	execute_fun(t_info *info)
{
	int		**fds;
	pid_t	*frs;
	t_node	*node;

	fds = NULL;
	frs = NULL;
	str_i_count(info);
	if (info->str_i > 0)
	{
		allocate_fds(&fds, &frs, info->str_i);
		info->fds = fds;
		info->frs = frs;
		info->i_fds = 0;
		while (info->i_fds < info->str_i + 1)
		{
			if (pipe(fds[info->i_fds++]) == -1)
			{
				error_pipe(fds, --info->i_fds, info);
				de_allocate(&fds, &frs, info->str_i);
				exit_number(1, info);
				return (1);
			}
		}
	}
	pwd_fun(info, -1);
	open_herdoc_files(info->first_node, info);
	node = info->first_node;
	info->is_open_files  = 1;
	check_open_files(&node, info);
	dir_blt_execve_fun(node, fds, frs, info);
	return (finish_parent(&fds, &frs, info));
}
