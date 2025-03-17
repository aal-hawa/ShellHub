/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:29 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:29:19 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**pwd_fun(t_info *info, int is_print)
{
	char	*cur_path;
	char	*str_join;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		info->status_exit = 1;
		return (NULL);
	}
	info->status_exit = 0;
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1);
	if (is_print == -1)
		return (NULL);
	str_join = ft_strjoin(info->curent_path, "\n");
	return (builtins_message(&str_join, is_print, 1));
}
