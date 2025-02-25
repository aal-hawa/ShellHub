# include "../minishell.h"


void	do_execve_fun(t_node **cmd_node, int **fds, pid_t *frs, t_info *info)
{
	if (!cmd_node[0])
		return ;
	if (cmd_node[0]->is_dir_bilt_cmd == 2 || cmd_node[0]->is_do_execute > 0)
	{
		// printf("do execve\n");
		if (cmd_node[0]->is_do_execute == 1)
			cmd_node[0]->args = move2next_arg(cmd_node);
		if (!ft_strcmp(cmd_node[0]->type_after, "|") && ft_strcmp(cmd_node[0]->type_before, ">") 
			&& cmd_node[0]->is_dir_bilt_cmd != 1) //!!?? //&& ft_strcmp(cmd_node[0]->type_before, ">")
			info->is_for_w = 2;
		frs[info->i_childs] = fork();
		if (frs[info->i_childs] == 0)
		{
			close_fds_childs(fds, info);
			childs(cmd_node[0], fds, frs, info);
		}
		info->fd_file_r = close_fd_fun(info->fd_file_r);
		info->is_builtins_file = 0;
		info->i_childs++;
		*cmd_node = NULL;
	}
	else
	{
		// printf("not for execve\n");
		// printf("cmd_node[0]->is_dir_bilt_cmd: %d\n", cmd_node[0]->is_dir_bilt_cmd);
		// printf("cmd_node[0]->is_do_execute: %d\n", cmd_node[0]->is_do_execute);
		// printf("cmd_node[0]->args[0]: %s\n", cmd_node[0]->args[0]);
	}
}

int	is_can_do_execve(t_node **node,t_node **cmd_node, t_info *info)
{
	if (info->is_exit_one == 1)
	{
		if (!ft_strcmp(node[0]->type_after, "|"))
			info->is_exit_one = 0;
		*node = node[0]->next;
		// if (*node)
			return (0);
	}
	if (node[0]->is_do_execute == -1)
	{
		cmd_node[0]->args = move2next_arg(cmd_node);
		node[0]->is_do_execute = 0;
		node[0]->is_dir_bilt_cmd = 1;
		return (0);
	}
	if (is_operator_output_fun(node[0]->type_after) || !ft_strcmp(node[0]->type_after, "|")
	|| !ft_strcmp(node[0]->type_after, "end") || node[0]->is_dir_bilt_cmd == 2 || info->is_builtins_file == 2)
	{
		if(!cmd_node[0])
			cmd_node[0] = *node;
		if (is_operator_output_fun(node[0]->type_after) && info->is_builtins_file == 0)
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


void	for_execve(t_node *node, int **fds, pid_t *frs, t_info *info, char **result_blts, t_node **cmd_node)
{
	if (node->is_dir_bilt_cmd != 1)
	{
		if (info->is_builtins_file == 1
			&& !is_operator_output_fun(node->type_after)
			&& is_operator_output_fun(node->type_before))
		{
			printf("print to file\n");
			info->is_builtins_file = 0;
			print_array2d_fd(result_blts, info->fd_file_w);
		}
		else
		{
			if (info->is_builtins_file == 2 || node->is_do_execute == 3)
			{
				// copy_node(cmd_node, &node, 0);
				// node->is_do_execute = 0;
				// info->is_no_inpipe = 1;
			}
			do_execve_fun(cmd_node, fds, frs, info);
			*cmd_node = NULL;
		}
	}


}
