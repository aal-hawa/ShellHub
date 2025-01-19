/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:35:53 by tmahmoud          #+#    #+#             */
/*   Updated: 2024/07/17 13:34:10 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skipwhitespace(const char *c, int *sign)
{
	while (*c == 32 || (*c >= 9 && *c <= 13))
		c++;
	if (*c == '-' || *c == '+')
	{
		if (*c == '-')
			*sign = -1;
		c++;
	}
	return (c);
}

int	ft_atoi(const char *str)
{
	unsigned int		i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	str = skipwhitespace(str, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i++] - '0');
		if (result > LLONG_MAX && sign == 1)
			return (-1);
		if (result > LLONG_MAX && sign == -1)
			return (0);
	}
	return (result * sign);
}
