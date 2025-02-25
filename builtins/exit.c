/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:17:08 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/25 20:49:20 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

void	exit_fun(char *arg, t_info *info)
{
	int	status_exit;
	(void)info;

	if (!arg)
		exit (0);
	if (!ft_isdigit(arg[0]))
		exit (2);
	status_exit = ft_atoi(arg);
	// free all things before exit program
	exit(status_exit % 256);
}

