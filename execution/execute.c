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
		return (1);
	}
	info->status_exit = 0;
	if (node->args[1])
	{
		if (is_biult_fun(node->args[1]) == 1)
			node->is_do_execute = -1;
		else
			node->is_do_execute = 1;
	}
	return (0);
}

void	builtins_fun(char	***result, t_node *node, t_info *info)
{
	int	is_print;

	is_print = 1;
	if (is_operator_fun(node->type_after) > 0 && !is_operator_input_fun(node->type_after))
		is_print = 0;
	if (!ft_strcmp(node->args[0], "cd"))
		result[0] = cd_fun(node->args, info, is_print);
	else if (!ft_strcmp(node->args[0], "echo"))
	{
		if (!ft_strcmp(node->args[1], "-n"))
			result[0] = echo_n_fun(node->args, is_print);
		else
			result[0] = echo_with_line_fun(node->args, is_print);
		info->status_exit = 0;
	}
	else if (!ft_strcmp(node->args[0], "env"))
		result[0] = env_fun(node->args, is_print);
	else if (!ft_strcmp(node->args[0], "export"))
		result[0] = export_fun(node->args, info, is_print);
	else if (!ft_strcmp(node->args[0], "unset"))
		result[0] = unset_func(node->args, info);
	else if (!ft_strcmp(node->args[0], "pwd"))
		result[0] = pwd_fun(info, is_print);
	else if (!ft_strcmp(node->args[0], "exit"))
		exit_fun();
}

void	do_execve_fun(t_node **cmd_node, int **fds, pid_t *frs, t_info *info)
{
	if (!cmd_node[0])
		return ;
	if (cmd_node[0]->is_dir_bilt_cmd == 2 || cmd_node[0]->is_do_execute > 0)
	{
		if (cmd_node[0]->is_do_execute == 1)
		{
			free(*(cmd_node[0]->args));
			cmd_node[0]->args++;
		}
		if (!ft_strcmp(cmd_node[0]->type_after, "|") && ft_strcmp(cmd_node[0]->type_before, ">")) //!!?? //&& ft_strcmp(cmd_node[0]->type_before, ">")
			info->is_for_w = 2;
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fds, info);
			childs(cmd_node[0], fds, frs, info);
		}
		info->i_childs++;
		*cmd_node = NULL;
	}
}
int	is_can_do_execve(t_node **node,t_node **cmd_node, t_info *info)
{
	if (node[0]->is_do_execute == -1)
	{
		free(*(cmd_node[0]->args));
		cmd_node[0]->args++;
		node[0]->is_do_execute = 0;
		node[0]->is_dir_bilt_cmd = 1;
		return (0);
	}
	if (is_operator_output_fun(node[0]->type_after) || !ft_strcmp(node[0]->type_after, "|")
	|| !ft_strcmp(node[0]->type_after, "end") || node[0]->is_dir_bilt_cmd == 2)
	{
		if(!cmd_node[0])
			cmd_node[0] = *node;
		if (is_operator_output_fun(node[0]->type_after) && info->is_builtins_file == 0) // new
		{
			*node = node[0]->next;
			if (*node)
				return (0);
		}
		if ((info->fd_file_w == -1 || info->fd_file_r == -1) && ft_strcmp(node[0]->type_after, "|"))
		{
			*node = node[0]->next;
			if (*node)
				return (0);
		};
	}
	return (1);
}

void	do_builtins(t_node *node, char ***result_blts, t_info *info)
{
	if (*result_blts)
	{
		free_array2d(*result_blts, 0);
		*result_blts = NULL;
	}
	builtins_fun(result_blts, node, info);
	if (*result_blts && is_operator_fun(node->type_after) > 0)
	{
		if (is_operator_fun(node->type_after) == 2)
		{
			info->is_builtins_file = 2;
			node->fd_file = init_files_biultins(*result_blts, info);
		}
		else
			info->is_builtins_file = 1;
		node->is_do_execute = 2;
	}
}

void	for_execve(t_node *node, int **fds, pid_t *frs, t_info *info, char **result_blts, t_node **cmd_node)
{
	if (node->is_dir_bilt_cmd != 1)
	{
		if (info->is_builtins_file == 1
			&& !is_operator_output_fun(node->type_after)
			&& is_operator_output_fun(node->type_before))
		{
			info->is_builtins_file = 0;
			print_array2d_fd(result_blts, info->fd_file_w);
		}
		else
			do_execve_fun(cmd_node, fds, frs, info);
	}
}

void	order_execve_fun(t_node *node, int **fds, pid_t *frs, t_info *info)
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
			do_builtins(node, &result_blts, info);
		if (!is_can_do_execve(&node, &cmd_node, info))
			continue;
		for_execve(node, fds, frs, info, result_blts, &cmd_node);
		if (node)
			node = node->next;
	}
	if (result_blts)
	{
		free_array2d(result_blts, 0);
		result_blts = NULL;
	}
}

int	execute_fun(t_info *info)
{
	int		**fds;
	pid_t	*frs;

	fds = NULL;
	frs = NULL;
	if (info->str_i > 0)
	{
		allocate_fds(&fds, &frs, info->str_i);
		info->i_fds = 0;
		while (info->i_fds < info->str_i + 1)
			if (pipe(fds[info->i_fds++]) == -1)
				return (error_pipe(fds, --info->i_fds, info, NULL),
					de_allocate(&fds, &frs, info->str_i), exit(1), 1);
	}
	pwd_fun(info, 0);
	order_execve_fun(info->first_node, fds, frs, info);
	return (finish_parent(&fds, &frs, info));
}
