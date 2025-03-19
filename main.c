/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:38:06 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/19 03:57:32 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nshellhub$ ", 12);
	g_global_variable = 1;
}

void	sigquit_handler(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

int	main(int ac, char **arg, char **envp)
{
	t_info	info;	

	g_global_variable = 0;
	setup_signals();
	(void)arg;
	if (ac != 1)
		return (1);
	init_info(envp, &info);
	env_data(&info);
	minishell(&info);
	return (0);
}
