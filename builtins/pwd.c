/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:20 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/09 19:28:31 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*pwd_fun(t_info *info)
{
	char *cur_path;

	cur_path = getcwd(NULL, 0);
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1);
	printf("info->curent_path: %s\n",info->curent_path);
	return (info->curent_path);
}