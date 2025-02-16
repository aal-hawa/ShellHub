/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:23:20 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/16 14:16:22 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	**pwd_fun(t_info *info, int is_print)
{
	char 	*cur_path;
	char	**result;

	cur_path = getcwd(NULL, 0);
	info->curent_path = ft_restore_value(&info->curent_path, &cur_path, 1);
	if (is_print == 1)
	printf("%s\n",info->curent_path);
	result = malloc(sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strdup(info->curent_path);
	return (result);
}