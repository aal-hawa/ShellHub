#include "../minishell.h"

int	check_valid_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	check_valid_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_is_valid_key(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || !check_valid_alpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(check_valid_alpha(str[i]) || check_valid_num(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int	is_has_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

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
	if (is_exist_str_in_2array(info->export, arg, 0) || 
		is_exist_str_in_2array(info->export, arg, ft_strlen(arg)))
	{
		// printf("\n------\ndeleting {{%s}}, adding with new value{{%s}}\n------\n", arg, arg);
		info->export = del_str_from_array2d(info->export, arg, 0);
		info->export = add_in_split(info->export, arg, 0);
	}
	else
	{
		// printf("\n------\nadding{{%s}}\n------\n", arg);
		info->export = add_in_split(info->export, arg, 1);
	}
	if (add_to_env)
		info->envp = add_in_split(info->envp, arg, 0);
}

void	print_value(char *arg, t_info *info, int print)
{
	int		i;
	char	*key;
	char	*value;
	char	*new_arg;

	i = 0;
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
			new_arg = ft_strjoin(key, "=");
			new_arg = ft_strjoin(new_arg, value);
		}
		else
			new_arg = ft_strdup(key);
		check_and_add(info, new_arg, 0);
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
	(void) is_print;
	int	i;

	i = 1;
	if (!info)
		return (NULL);
	if (!args[i])
		print_export(info);
	else
	{
		while (args[i])
		{
			print_value(args[i], info, 0);
			i++;
		}
	}
	return (info->export);
}
