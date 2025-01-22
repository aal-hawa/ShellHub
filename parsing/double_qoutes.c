/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_qoutes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:10:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/22 15:14:17 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// send str from first char after double qoutes
// return NULL if did not have second double qoutes
// return dest between the double qoutes
char *double_quot_fun(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\"')
		i++;
	if (!str[i])
		return (NULL);
	dest = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '\"')
	{
		dest[i] = str[i];
		i++;
	}
	return (dest);
}
