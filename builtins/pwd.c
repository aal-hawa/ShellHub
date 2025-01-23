/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:20 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 17:17:34 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*pwd_fun(t_info *info)
{
	char *cur_path;

	cur_path = getcwd(NULL, 0);
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1) ;
	return (info->curent_path);
}