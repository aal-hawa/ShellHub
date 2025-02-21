/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:57:52 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/21 19:29:04 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

char	**echo_n_fun(char **args, int is_print)
{
	char	**result;

	if (!*args || !*args)
		return (NULL);
	result = copy_split(&args[2]);
	if (!result)
		return (NULL);
	if (is_print == 1)
		print_array2d(result, 0);
	return (result);
}

char	**echo_with_line_fun(char **args, int is_print)
{

	char	**result;

	if (!*args || !*args)
		return (NULL);
	result = copy_split(&args[1]);
	result = add_in_split(result, "\n", 0);
	if (!result)
		return (NULL);
	if (is_print == 1)
		print_array2d(result, 0);
	return (result);
}