/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:57 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 18:03:22 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	str_i_count(t_info *info)
{
	t_token	*token;

	token = info->tokens;
	while (token)
	{
		if (token->next)
			info->str_i++;
		token = token->next;
	}
	if (info->str_i > 0)
		info->str_i++;
	else if (info->str_i == 0)
	{
		token = info->tokens;
		if (token->is_bilt_cmd == 1)
			info->str_i++;
	}
}

void	dir_blt_execve_fun(t_token *tokens, t_info *info)
{
	char	**result_blts;

	result_blts = NULL;
	while (tokens)
	{
		if (!check_open_files(tokens, info))
		{
			if (tokens->cmd)
			{
				if (tokens->is_bilt_cmd == 0)
					do_builtins_check_fork(tokens, info, &result_blts);
				else
					for_execve(tokens, info);
			}
			else if (info->str_i > 0)
				execve_no_cmd(info);
		}
		tokens = tokens->next;
	}
	if (result_blts)
		free_array2d(&result_blts, 0);
}

void	execute_fun(t_info *info)
{
	str_i_count(info);
	if (init_pipes(info) == 1)
		return ;
	pwd_fun(info, -1);
	open_herdoc_files(info->herdoc_files, info);
	put_name_herdoc_files(info);
	dir_blt_execve_fun(info->tokens, info);
	finish_parent(info);
}
