/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:33:53 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/08 05:58:10 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_has_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

static char **add_to_env(char **arr, char *arg)
{
	if (is_exist_str_in_2array(arr, arg, 0) || 
		is_exist_str_in_2array(arr, arg, ft_strlen(arg)))
	{
		arr = del_str_from_array2d(arr, arg, 0);
		arr = add_in_split(arr, arg, 0);
	}
	else
	{
		arr = add_in_split(arr, arg, 1);
	}
	return (arr);
}

static int check_valid_args(char **arr)
{
	int	i;

	i = 1;
	while(arr[i])
	{
		if(!is_has_equal(arr[i]))
		{
			printf("env: %s: No such file directly\n", arr[i]);
			return(0);
		}
		i++;
	}
	return (1);
}

static void print_env(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		printf("%s\n", arr[i++]);
}

char	**env_fun(char **args, t_info * info, int is_print)
{
	int i = 1;
	char **cpy_print = NULL;
	cpy_print = copy_split(info->envp);
	if(args[i])
	{
		if(!check_valid_args(args))
			return (NULL);
		else
		{
			while(args[i])
				cpy_print = add_to_env(cpy_print, args[i++]);
		}
	}
	if(is_print)
		print_env(cpy_print);
	return (cpy_print);
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