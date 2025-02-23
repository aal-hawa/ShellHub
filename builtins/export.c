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

void	check_and_add(t_info *info, char *arg)
{
	(void) info;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = strndup(arg, i);
	value = NULL;
	if (arg[i] == '=')
		value = strdup(arg + i + 1);
	if (!check_is_valid_key(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		if (value)
			free(value);
		return ;
	}
	printf("Adding key: %s, value: %s\n", key, value ? value : "(null)");
	free(key);
	if (value)
		free(value);
}

void	print_export(t_info *info)
{
	int	i;

	i = 0;
	while (info->export[i])
	{
		printf("declare -x ");
		add_double_quotes(info->export[i]);
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
			check_and_add(info, args[i]);
			i++;
		}
	}
	return (NULL);
}
