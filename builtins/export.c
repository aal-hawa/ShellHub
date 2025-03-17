/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:21:25 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:21:26 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_and_add(t_info *info, char *arg, int add_to_env)
{
	char	*key;

	key = ft_strdup(arg);
	key = join_with_restore(&key, "declare -x ", key, NULL);
	ft_add_qout_export(&key, ft_strlen(key));
	if (is_exist_str_in_2array(info->export, key))
	{
		info->export = del_str_from_array2d(&info->export, key);
		info->export = add_in_array2d(&info->export, key, 0);
	}
	else
		info->export = add_in_array2d(&info->export, key, 1);
	if (add_to_env)
		info->envp = add_in_array2d(&info->envp, arg, 0);
	key = free_string(&key);
}

void	check_and_add_env(t_info *info, char *arg, char *key)
{
	if (is_exist_str_in_2array(info->envp, key))
	{
		info->envp = del_str_from_array2d(&info->envp, arg);
		info->envp = add_in_array2d(&info->envp, arg, 0);
	}
	else
		info->envp = add_in_array2d(&info->envp, arg, 1);
}

void	got_key_value(char *arg, char **key, char **value)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*key = ft_strndup(arg, i);
	if (arg[i] == '=')
		*value = ft_strdup(arg + i + 1);
}

void	print_value(char *arg, t_info *info)
{
	char	*key;
	char	*value;
	char	*new_arg;

	new_arg = NULL;
	value = NULL;
	key = NULL;
	got_key_value(arg, &key, &value);
	if (!check_is_valid_key(key))
		printf("minishell: export: `%s': not a valid identifier\n", key);
	else if (value)
	{
		new_arg = join_with_restore(&new_arg, key, "=", value);
		check_and_add(info, new_arg, 0);
		check_and_add_env(info, new_arg, key);
		new_arg = free_string(&new_arg);
	}
	else
		check_and_add(info, key, 0);
	key = free_string(&key);
	value = free_string(&value);
}

char	**export_fun(char **args, t_info *info, int is_print)
{
	int	i;

	i = 1;
	if (!info)
		return (NULL);
	if (!args[i])
	{
		if (is_print == 1)
			print_array2d(info->export, 1);
		else
			return (copy_array2d(info->export, 1));
	}
	else
	{
		while (args[i])
		{
			print_value(args[i], info);
			i++;
		}
		env_data(info);
	}
	return (NULL);
}
