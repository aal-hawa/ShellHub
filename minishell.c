/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:37:17 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:37:31 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_files(t_info *info)
{
	int		i;
	char	*str;
	char	*str_i;

	i = 0;
	if (info->index_files_crt > 0)
	{
		while (i < info->index_files_crt)
		{
			str_i = ft_itoa(i);
			str = ft_strjoin("/tmp/tmp_shell_", str_i);
			unlink(str);
			str_i = free_string(&str_i);
			str = free_string(&str);
			i++;
		}
	}
	info->index_files_crt = 0;
}

void	null_line(t_info *info)
{
	write(1, "exit\n", 5);
	exit_number(0, 0, info);
}

void	minishell(t_info *info)
{
	char	*line;

	while (1)
	{
		line = readline_fun();
		if (!line)
			null_line(info);
		if (!check_valid_line(&line, info))
			continue ;
		fixed_line_spaces(&line);
		line = find_doller_sign_fun(&line, info);
		line = tilde(&line, info->home);
		create_nodes(line, info);
		line = free_string(&line);
		if (info->tokens)
		{
			execute_fun(info);
			unlink_files(info);
		}
		reset_info(info);
	}
}
