/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:48 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 00:01:49 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtins_fun(char ***result, char **biultins, t_info *info,
		int is_print)
{
	if (!ft_strcmp(biultins[0], "cd"))
		result[0] = cd_fun(biultins, info);
	else if (!ft_strcmp(biultins[0], "echo"))
	{
		if (check_echo_n(biultins[1]))
			result[0] = echo_n_fun(biultins, is_print);
		else
			result[0] = echo_with_line_fun(biultins, is_print);
		info->status_exit = 0;
	}
	else if (to_lower_pwd_env(biultins[0]) == 2)
		result[0] = env_fun(biultins, info, is_print);
	else if (!ft_strcmp(biultins[0], "export"))
		result[0] = export_fun(biultins, info, is_print);
	else if (!ft_strcmp(biultins[0], "unset"))
		result[0] = unset_func(biultins, info);
	else if (to_lower_pwd_env(biultins[0]) == 1)
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

void	do_builtins_check_fork(t_token *token, t_info *info,
	char ***result_blts)
{
	if (info->str_i > 0)
	{
		info->frs[info->i_childs] = fork();
		if (info->frs[info->i_childs] == 0)
		{
			if (do_builtins(token, result_blts, info) == 1)
			{
				dup2(info->fds[info->i_childs + 1][1], STDOUT_FILENO);
				print_array2d_fd(*result_blts, STDOUT_FILENO);
			}
			close_fds_childs(info->fds, info);
			close(info->fds[info->i_childs + 1][1]);
			close(info->fds[info->i_childs][0]);
			if (info->str_i > 0)
				de_allocate(&info->fds, &info->frs, info->str_i);
			free_array2d(result_blts, 0);
			exit_number(info->status_exit, 0, info);
		}
		info->fd_file_w = close_fd_fun(info->fd_file_w);
		info->i_childs++;
	}
	else
		do_builtins(token, result_blts, info);
}
