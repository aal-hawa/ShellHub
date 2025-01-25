/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:27:51 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 17:07:17 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_restore_value(char **dest, char **str, int is_str_malloc)
{
	free_fun(dest);
	*dest = ft_strdup(*str);
	if (!*dest)
		return (NULL);
	if (is_str_malloc == 1)
		free_fun(str);
	return (*dest);
}