#include "../minishell.h"


void	add_double_quotes(char *str)
{
	int		len;
	int		i;
	char	*new_str;

	len = strlen(str);
	new_str = malloc(sizeof(char) * (len + 3));
	if (!new_str)
		return ;
	new_str[0] = '"';
	i = 0;
	while (str[i])
	{
		new_str[i + 1] = str[i];
		i++;
	}
	new_str[i + 1] = '"';
	new_str[i + 2] = '\0';
	printf("%s\n", new_str);
	free(new_str);
}

void	check_and_add(t_info *info, char *arg, int add_to_env)
{
	if (is_exist_str_in_2array(info->export, arg, 0))
	{
		info->export = del_str_from_array2d(&info->export, arg);
		info->export = add_in_array2d(&info->export, arg, 0);
	}
	else
		info->export = add_in_array2d(&info->export, arg, 1);
	if (add_to_env)
		info->envp = add_in_array2d(&info->envp, arg, 0);
}

void	check_and_add_env(t_info *info, char *arg, char *key)
{
	if (is_exist_str_in_2array(info->envp, key, 0))
	{
		info->envp = del_str_from_array2d(&info->envp, arg);
		info->envp = add_in_array2d(&info->envp, arg, 0);
	}
	else
		info->envp = add_in_array2d(&info->envp, arg, 1);
}

void	print_value(char *arg, t_info *info, int print)
{
	int		i;
	char	*key;
	char	*value;
	char	*new_arg;

	i = 0;
	new_arg = NULL;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_strndup(arg, i);
	value = NULL;
	if (arg[i] == '=')
		value = strdup(arg + i + 1);
	if (!check_is_valid_key(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		free(value);
		return ;
	}
	key = ft_join_with_restore(&key, "declare -x ", key);

	if (print)
	{
		printf("%s", key);
		if (value)
		{
			printf("=");
			add_double_quotes(value);
		}
		else
			printf("\n");
	}
	else
	{
		if (value)
		{
			new_arg = ft_join_with_restore(&new_arg, key, "=");
			new_arg = ft_join_with_restore(&new_arg, new_arg, value);
			check_and_add(info, new_arg, 0);
			check_and_add_env(info, new_arg, key);
		}
		else
		{
			new_arg = ft_strdup(key);
			check_and_add(info, new_arg, 0);
		}
		free(new_arg);
	}
	free(key);
	free(value);
}


void	print_export(t_info *info)
{
	int	i;

	i = 0;
	while (info->export[i])
	{
		printf("declare -x ");
		print_value(info->export[i], info, 1);
		i++;
	}
}

char	**export_fun(char **args, t_info *info, int is_print)
{
	int	i;
	char **cp_export;

	cp_export = NULL;
	i = 1;
	if (!info)
		return (NULL);
	if (!args[i] && is_print)
		print_array2d(info->export, 1);
	else
	{
		while (args[i])
		{
			print_value(args[i], info, 0);
			i++;
		}
	}
	// cp_export = make_export_fun(info->export);
	// env_data(info);
	return (cp_export);
}
