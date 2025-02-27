# include "../minishell.h"

void	str_i_count(t_info *info)
{
	t_node	*node;

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
	// printf ("info->str_i: %d\n", info->str_i);
}
void	do_builtins_check_fork(t_node *node,  t_info *info, char ***result_blts)
{
	pid_t	frs_1;
	if (info->str_i > 0 && 
		(ft_strcmp(node->args[0], "pwd") || (!ft_strcmp(node->args[0], "export") && node->args[1])))
	{
		printf ("aaaaaaaaaaaaaaaa\n");
		frs_1 = fork();
		if (frs_1 == 0)
		{
			do_builtins(node, result_blts, info);
			if (info->is_builtins_file == 1
				&& !is_operator_output_fun(node->type_after)
				&& is_operator_output_fun(node->type_before))
			{
				printf("ddddddddddddddd\n");
				printf("print to file\n");
				info->is_builtins_file = 0;
				print_array2d_fd(*result_blts, info->fd_file_w);
			}
			exit (info->status_exit);
		}
	}
	else
		do_builtins(node, result_blts, info);
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
		info->is_for_w = 0;
		if (node->is_dir_bilt_cmd == 0)
			direct_fun(node, info);
		else if (node->is_dir_bilt_cmd == 1)
			do_builtins_check_fork(node, info, &result_blts);
		if (!is_can_do_execve(&node, &cmd_node, info))
			continue;
		for_execve(node, fds, frs, info, result_blts, &cmd_node);
		if (node)
			node = node->next;
	}
	if (result_blts)
		free_array2d(&result_blts, 0);
}

int	execute_fun(t_info *info)
{
	int		**fds;
	pid_t	*frs;

	fds = NULL;
	frs = NULL;
	str_i_count(info);
	if (info->str_i > 0)
	{
		allocate_fds(&fds, &frs, info->str_i);
		info->i_fds = 0;
		while (info->i_fds < info->str_i + 1)
		{
			if (pipe(fds[info->i_fds++]) == -1)
			{
				error_pipe(fds, --info->i_fds, info, NULL);
				de_allocate(&fds, &frs, info->str_i);
				exit(1);
				return (1);
			}
		}
	}
	pwd_fun(info, -1);
	dir_blt_execve_fun(info->first_node, fds, frs, info);
	return (finish_parent(&fds, &frs, info));
}
