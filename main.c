/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:38:06 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:38:14 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\nshellhub$ ", 12);
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

	setup_signals();
	(void)arg;
	if (ac != 1)
		return (1);
	init_info(envp, &info);
	env_data(&info);
	minishell(&info);
	return (0);
}
