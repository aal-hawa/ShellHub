# include "../minishell.h"

void	builtins_fun(char	***result, char **biultins, t_info *info, int is_print)
{
	if (!ft_strcmp(biultins[0], "cd"))
		result[0] = cd_fun(biultins, info);
	else if (!ft_strcmp(biultins[0], "echo"))
	{
		if (!ft_strcmp(biultins[1], "-n"))
			result[0] = echo_n_fun(biultins, is_print);
		else
			result[0] = echo_with_line_fun(biultins, is_print);
		info->status_exit = 0;
	}
	else if (!ft_strcmp(biultins[0], "env"))
		result[0] = env_fun(biultins, info, is_print);
	else if (!ft_strcmp(biultins[0], "export"))
		result[0] = export_fun(biultins, info, is_print);
	else if (!ft_strcmp(biultins[0], "unset"))
		result[0] = unset_func(biultins, info);
	else if (!ft_strcmp(biultins[0], "pwd"))
		result[0] = pwd_fun(info, is_print);
	else if (!ft_strcmp(biultins[0], "exit"))
		exit_fun(biultins, info);
}

int	do_builtins(t_token *token, char ***result_blts, t_info *info)
{
	int	is_print;

	is_print = 1;
	if (token->next || info->fd_file_w >= 0)
		is_print = 0;
	if (*result_blts)
		free_array2d(result_blts, 0);
	builtins_fun(result_blts, token->cmd, info, is_print);

	if (*result_blts && is_print == 0)
	{
		if (info->fd_file_w >= 0)
		{
			print_array2d_fd(*result_blts, info->fd_file_w);
			info->fd_file_w = close_fd_fun(info->fd_file_w);
		}
		else if (token->next)
			return (1);
	}
	return (0);
}
