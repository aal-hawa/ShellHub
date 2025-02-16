/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:33:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/15 17:35:40 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*env_fun(char *name)
{
	
	return (getenv(name));
}




// HOME=99=99


// search about charcter, if exist split to two sections (before the chracter) (After the chracter)
/* 
char **funcName (char *str, char c)
{
	ft_split
	ft_strjoin
}
char **result = funcName(str, c);
if(result == null)
	ToDo
else
Continue work

int funcName (char *str, char c, char **before_sign, char **after_sign)
*/

char **split_export_input()
{
	
}

char **split_env_arg(char *str, char c)
{
	char **result;
	char *str_after_sign;
	int i;

	i = 1;
	str_after_sign = NULL;
	result = ft_split(str, c);
	if(result[2] != "\0")
	while (result[i])
	{
		str_after_sign = ft_strjoin(str_after_sign, result[i]);
		free(result[i]);
		result[i++] = NULL;
	}
	return (result);
}