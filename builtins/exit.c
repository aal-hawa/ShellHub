/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:17:08 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/26 19:03:38 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	exit_fun(char **arg, t_info *info)
{
	int	status_exit;
	(void)info;
	int	i;
	
	if (!arg[1])
		exit (0);
	i = -1;
	if (len_split(arg) > 2)
	{
		while (arg[1][++i])
		{
			if (!ft_isdigit(arg[1][i]))
			{
				builtins_error_message("exit", arg[1]);
				exit (255);
			}
		}
		printf("bash: exit: too many arguments\n");
		return ;
	}
	if (!ft_isdigit(arg[1][0]))
		exit (2);
	status_exit = ft_atoi(arg[1]);
	// free all things before exit program
	exit(status_exit % 256);
}

