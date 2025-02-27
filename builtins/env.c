/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:33:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/27 14:39:21 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_fun(char **args, t_info * info, int is_print)
{
	(void)args;
	(void)is_print;

	// return (getenv(name));
	return (args);
}
// char **result = funcName(str, c);
// if(result == null)
// 	ToDo
// else
// Continue work

// int funcName (char *str, char c, char **before_sign, char **after_sign)
// */

// char **split_export_input()
// {
	
// }

// char **split_env_arg(char *str, char c)
// {
// 	char **result;
// 	char *str_after_sign;
// 	int i;

// 	i = 1;
// 	str_after_sign = NULL;
// 	result = ft_split(str, c);
// 	if(result[2] != "\0")
// 	while (result[i])
// 	{
// 		str_after_sign = ft_strjoin(str_after_sign, result[i]);
// 		free(result[i]);
// 		result[i++] = NULL;
// 	}
// 	return (result);
// }