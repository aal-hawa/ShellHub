/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restore_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:27:51 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/27 21:13:52 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_restore_value(char **dest, char **str, int is_str_malloc)
{
	if (!str || !*str)
		return (*dest);
	*dest = free_string(dest);
	*dest = ft_strdup(*str);
	if (!*dest)
		return (NULL);
	if (is_str_malloc == 1)
		*str = free_string(str);
	return (*dest);
}
