# include "../minishell.h"

int	direct_fun(t_node *node, t_info *info)
{
	if (!ft_strcmp(node->type_before,">"))
	{
		info->fd_file_w = open_file_w(node->args[0]);
		info->is_for_w = 1;
		node->fd_file = info->fd_file_w;
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
	if (info->fd_file_w == -1)
	{
		info->is_exit_one = 1;
		return (1);
	}
	if (node->args[1])
		node->is_do_execute = 1;
	return (0);
}

char	*builtins_fun(t_node *node, t_info *info)
{
	char	*result;

	result = NULL;
	if (!ft_strcmp(node->args[0], "cd"))
		result = cd_fun(node->args[1], info);
	else if (!ft_strcmp(node->args[0], "echo"))
	{
		if (!ft_strcmp(node->args[1], "-n"))
			result = echo_n_fun(node->args[2]);
		else
			result = echo_with_line_fun(node->args[1]);
	}
	else if (!ft_strcmp(node->args[0], "env"))
		result = env_fun(node->args[1]);
	else if (!ft_strcmp(node->args[0], "export"))
		export_fun(node->args[1], info);
	else if (!ft_strcmp(node->args[0], "unset"))
		unset_func(node->args[1], info);
	else if (!ft_strcmp(node->args[0], "pwd"))
		result = pwd_fun(info, 1);
	else if (!ft_strcmp(node->args[0], "exit"))
		exit_fun();
	// if (result && is_operator_fun(node->type_after) == 0)
	// 	printf("%s", result);
	return (result);
}

void	order_execve_fun(t_node *node, int **fd1, pid_t *frs, t_info *info)
{
	char	*result_blts;

	info->i_childs = 0;
	if (info->fd_file_r == -1)
		info->i_childs = 1;
	while (node)
	{
		info->is_for_w = 0;
		if (node->is_dir_bilt_cmd == 0)
		{
			if (direct_fun(node, info) == 1)
				break ;
		}
		else if (node->is_dir_bilt_cmd == 1)
		{
			result_blts = builtins_fun(node, info);
			if (result_blts && is_operator_fun(node->type_after) == 1)
				init_files_biultins(result_blts, info);
		}
		if (node->is_dir_bilt_cmd == 2 || node->is_do_execute == 1) 
		{
			if (node->is_do_execute == 1)
			{
				printf ("node->is_do_execute %d\n",node->is_do_execute);
				free(*node->args);
				node->args++;
			}
			// printf ("info->fd_file_r %d\n",info->fd_file_r);
			if (!ft_strcmp(node->type_after, "|"))
			{
				info->is_for_w = 2;
				printf ("aaaaaaaaaa\n");
			}
			frs[info->i_childs] = fork();
			if (frs[info->i_childs] == 0)
			{
				close_fds_childs(fd1, info);
				childs(node, fd1, frs, info);
			}
			info->i_childs++;
		}
		node = node->next;
	}
}

int	execute_fun(t_info *info)
{
	int		**fd1;
	pid_t	*frs;

	fd1 = NULL;
	frs = NULL;
	if (info->str_i > 0)
	{
		allocate_fds(&fd1, &frs, info->str_i);
		// info->offset = init_files(str, info);
		info->i_fds = 0;
		while (info->i_fds < info->str_i + 1)
			if (pipe(fd1[info->i_fds++]) == -1)
				return (error_pipe(fd1, --info->i_fds, info, NULL),
					de_allocate(&fd1, &frs, info->str_i), exit(1), 1);
	}
	info->curent_path = pwd_fun(info, 0);
	// init_childs(str, fd1, frs, info);
	order_execve_fun(info->first_node, fd1, frs, info);
	return (finish_parent(&fd1, &frs, info));
}
