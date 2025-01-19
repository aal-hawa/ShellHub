/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 20:50:42 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/07/17 18:28:40 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	i;
	char			*str;

	i = ft_strlen(s1) + 1;
	str = ft_calloc(sizeof(char), i);
	ft_strlcpy(str, s1, i);
	return (str);
}
