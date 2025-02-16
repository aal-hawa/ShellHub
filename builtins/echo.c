/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:57:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/16 14:01:56 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	**echo_n_fun(char *str, int is_print)
{
	char	**result;

	if (!str)
		return (NULL);
	result = malloc (sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strdup(str);
	if (is_print == 1)
		printf("%s", str);
	return (result);
}

char	**echo_with_line_fun(char *str, int is_print)
{
	char	**result;

	if (!str)
		return (NULL);
	result = malloc (sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strjoin(str, "\n");
	if (is_print == 1)
		printf("%s\n", str);
	return (result);
}