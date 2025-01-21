/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:45:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/21 15:54:08 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int	export_func(char *name, t_info *info)
{
	char	*export;
	if (!getenv(name))
	{
		export = malloc(name);
		if (!export)
			return (-1);
		// add in info->env
	}
	return (0);
}