/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:54:21 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/21 15:55:53 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	unset_func(char *name, t_info *info)
{
	char	*unset;
	if (getenv(name))
	{
		// remove from info->env
		return(0); // for only if condetion work
	}
	return (0);
}