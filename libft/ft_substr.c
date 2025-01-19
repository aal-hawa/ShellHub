/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:11:55 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/07/20 03:48:05 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*resut;

	if (!s || ft_strlen(s) <= start || !len)
		return (ft_strdup(""));
	else if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	resut = ft_calloc(sizeof(char), (len + 1));
	if (!resut)
		return (NULL);
	ft_strlcpy(resut, s + start, len + 1);
	return (resut);
}
