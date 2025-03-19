/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:15 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 03:06:24 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_fds(void)
{
	int	i;

	i = 1000;
	while (i > 0)
		close(i--);
}

void	exit_number(int exit_status, int is_de_allocate, t_info *info)
{
	if (is_de_allocate == 1)
		de_allocate(&info->fds, &info->frs, info->str_i);
	unlink_files(info);
	free_info(info);
	close_all_fds();
	exit(exit_status);
}

void	exit_fun(char **arg, t_info *info)
{
	int	status_exit;
	int	i;

	if (!arg[1])
		exit_number(0, 1, info);
	i = -1;
	if (len_array2d(arg) > 2)
	{
		while (arg[1][++i])
		{
			if (!ft_isdigit(arg[1][i]))
			{
				builtins_error_message("exit", arg[1]);
				exit_number(255, 1, info);
			}
		}
		printf("bash: exit: too many arguments\n");
		return ;
	}
	if (!ft_isdigit(arg[1][0]))
		exit_number(255, 1, info);
	status_exit = ft_atoi(arg[1]);
	exit_number(status_exit % 256, 1, info);
}
