/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:55:44 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 17:19:39 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	*cd_fun(char *cd, t_info *info)
{
	if (!ft_strcmp(cd,".."))
		info->curent_path = ft_strlchr(&info->curent_path, '/', 1);
	else
		info->curent_path = ft_restore_value(&info->curent_path, ft_strjoin(info->curent_path, cd), 1);
	if (chdir(info->curent_path))
	{
		printf ("Error path: %s\n", cd);
		pwd_fun(info);
	}
	return(info->curent_path);
}
