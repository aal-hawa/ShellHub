# include "../minishell.h"

void	builtins_fun(char	***result, t_node *node, t_info *info)
{
	int	is_print;
	pid_t	frs;
	is_print = 1;
	if (is_operator_fun(node->type_after) > 0 && !is_operator_input_fun(node->type_after))
		is_print = 0;
	if (!ft_strcmp(node->args[0], "cd"))
	{
		if (info->str_i > 0)
		{
			printf ("aaaaaaaaaaaaaaaa\n");
			frs = fork();
			if (frs == 0)
			{
				result[0] = cd_fun(node->args, info, is_print);
				exit (info->status_exit);
			}
		}
		else
			result[0] = cd_fun(node->args, info, is_print);
	}
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
		exit_fun(node->args, info);
}

void	do_builtins(t_node *node, char ***result_blts, t_info *info)
{
	if (*result_blts)
		free_array2d(result_blts, 0);
	builtins_fun(result_blts, node, info);
	if (*result_blts && is_operator_fun(node->type_after) > 0)
	{
		if (is_operator_fun(node->type_after) == 2)
		{
			info->is_builtins_file = 2;
			node->fd_file = init_files_biultins(*result_blts, info);
			info->fd_file_r = node->fd_file;
		}
		else
			info->is_builtins_file = 1;
		node->is_do_execute = 2;
	}
}
