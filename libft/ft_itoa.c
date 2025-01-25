/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:09:21 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/25 17:07:46 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countfunction(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	count = countfunction(n);
	result = malloc(sizeof(char) * (count + 1));
	if (!result)
		return (NULL);
	result[count] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	while (count-- > 0 && n > 0)
	{
		result[count] = (n % 10) + '0';
		n /= 10;
	}
	return (result);
}
