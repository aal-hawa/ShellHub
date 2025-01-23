/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:54:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 19:00:30 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	unset_func(char *name, t_info *info)
{
	char	*unset;
	if (getenv(name))
	{
		// remove from info->env
		info->env = del_from_split(info->env, name);
		return(0); // for only if condetion work
	}
	return (1);
}