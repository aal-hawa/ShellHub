/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:45:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/16 16:26:26 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	**export_fun(char *name, t_info *info, int is_print)
{
	//delete (void) when create the function
	(void)name;
	(void)is_print;
	if (!info)
		return (NULL);
	// if (!getenv(name))
	// {
	// 	info->envp = add_in_split(info->envp, name, 1);
	// 	return (0);
	// }
	return (NULL);
}