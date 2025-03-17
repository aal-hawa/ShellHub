/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:10 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:21:13 by aal-hawa         ###   ########.fr       */
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

static char	**add_to_env(char ***arr, char *arg)
{
	if (is_exist_str_in_2array(*arr, arg))
	{
		*arr = del_str_from_array2d(arr, arg);
		*arr = add_in_array2d(arr, arg, 0);
	}
	else
	{
		*arr = add_in_array2d(arr, arg, 1);
	}
	return (*arr);
}

static int	check_valid_args(char **arr)
{
	int	i;

	i = 1;
	while (arr[i])
	{
		if (!is_has_equal(arr[i]))
		{
			printf("env: %s: No such file directly\n", arr[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**env_fun(char **args, t_info *info, int is_print)
{
	int		i;
	char	**cpy_print;
	char	**cpy_print_with_n;

	i = 1;
	cpy_print_with_n = NULL;
	if (args[i] && !check_valid_args(args))
		return (NULL);
	cpy_print = copy_array2d(info->envp, 0);
	if (args[i])
	{
		while (args[i])
			cpy_print = add_to_env(&cpy_print, args[i++]);
	}
	if (is_print)
		print_array2d(cpy_print, 1);
	else
		cpy_print_with_n = copy_array2d(cpy_print, 1);
	free_array2d(&cpy_print, 0);
	return (cpy_print_with_n);
}
