
#include "../minishell.h"

int	is_exist_str_in_2array(char **array2d, char *del_str, int size_str)
{
	int		i;
	
	i = -1;
	while (array2d && array2d[++i])
	{
		if (size_str == 0)
		{
			if (!ft_strccmp(array2d[i], del_str, '='))
				return (i);
		}
		else if (!ft_strncmp(array2d[i], del_str, size_str))
			return (i);
	}
	return (-1);
}
int	len_split(char **split)
{
	int	len;

	len = 0;
	if (!split)
		return (len);
	while (split[len])
		len++;
	return (len);
}
char	**copy_split(char **split)
{
	int	i;
	int	len;
	char	**new_split;

	i = 0;
	if (!split)
		return (NULL);
	len = len_split(split);
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	while (i < len)
	{
		new_split[i] = ft_strdup(split[i]);
		i++;
	}
	new_split[i] = NULL;
	return (new_split);
}

// check if you want share adress of split three pointers
char	**del_str_from_array2d(char **array2d, char *del_str, int size_str)
{
	int		i;
	int		y;
	int		len;
	char	**new_split;
	char	*str_zero;
	int		z;

	z = is_exist_str_in_2array(array2d, del_str, 0);
	if ( z == -1)
		return (array2d); 
	i = -1;
	y = -1;
	len = len_split(array2d);
	new_split = malloc(sizeof(char *) * (len));
	if (!new_split)
		return (NULL);
	while (array2d[++i])
	{
		if (size_str == 0)
		{
			if (i != z)
			{
				new_split[++y] = ft_strdup(array2d[i]);
				if (!new_split[y])
					return (free_string(&str_zero), free_array2d(&new_split, y - 1), NULL);
			}
		}
		else if (ft_strncmp(array2d[i], del_str, size_str))
		{
			new_split[++y] = ft_strdup(array2d[i]);
			if (!new_split[y])
				return (free_string(&str_zero), free_array2d(&new_split, y - 1), NULL);
		}
	}
	new_split[++y] = NULL;
	return (free_array2d(&array2d, len), new_split);
}
// alpha:
char	**add_in_split(char **split, char *add_str, int is_alpha)
{
	int		i;
	int		j;
	int		len;
	char	**new_split;

	i = 0;
	j = 0;
	len = len_split(split) + 1;
	new_split = malloc(sizeof(char *) * (len + 1));
	if (!new_split)
		return (NULL);
	while (split && split[i])
	{
		if (is_alpha == 1 && ft_strcmp(split[i], add_str) > 0 && is_alpha++)
			new_split[j] = ft_strdup(add_str);
		else
			new_split[j] = ft_strdup(split[i++]);
		if (!new_split[j++])
			return(free_array2d(&new_split, j - 2), NULL);
	}
	if (!split || is_alpha < 2)
		new_split[j++] = ft_strdup(add_str);
	new_split[j] = NULL;
	free_array2d(&split, len - 1);
	return (new_split);
}

char	**marge_2_splits(char ***first_split, char ***second_split)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new_split;

	i = 0;
	len1 = len_split(*first_split);
	len2 = len_split(*second_split);
	new_split = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_split)
		return (NULL);
		
	while (*first_split && first_split[0][i])
	{
		new_split[i] = ft_strdup(first_split[0][i]);
		if (!new_split[i])
			return(free_array2d(&new_split, i - 1), NULL);
		i++;
	}
	j = 0;
	while (*second_split && second_split[0][j])
	{
		new_split[i] = ft_strdup(second_split[0][j]);
		if (!new_split[i])
			return(free_array2d(&new_split, i - 1), NULL);
		i++;
		j++;
	}
	new_split[i] = NULL;
	free_array2d(first_split, len1);
	free_array2d(second_split, len2);
	return (new_split);
}


void	add_double_quotes_1(char **str)
{
	int		len;
	int		i;
	char	*new_str;

	len = strlen(*str);
	new_str = malloc(sizeof(char) * (len + 3));
	if (!new_str)
		return ;
	new_str[0] = '"';
	i = 0;
	while (str[0][i])
	{
		new_str[i + 1] = str[0][i];
		i++;
	}
	new_str[i + 1] = '"';
	new_str[i + 2] = '\0';
	*str = free_string(str);
	*str = new_str;
	printf("%s\n", new_str);
}

char	*print_value_1(char *arg)
{
	int		i;
	char	*key;
	char	*value;
	char	*result;
	char	*str_join;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	key = ft_strndup(arg, i);
	value = NULL;
	if (arg[i] == '=')
		value = ft_strdup(arg + i + 1);
	if (!check_is_valid_key(key))
	{
		printf("minishell: export: `%s': not a valid identifier\n", key);
		free(key);
		free(value);
		return (NULL);
	}
	str_join = ft_strjoin("declare -x ",key);
	result = ft_restore_value(&result, &str_join, 1);
	if (value)
	{
		str_join = ft_strjoin(result, "=");

		result = ft_restore_value(&result, &str_join, 1);
		add_double_quotes_1(&value);

		str_join = ft_strjoin(result, value);
		result = ft_restore_value(&result, &str_join, 1);
	}
	// else
	// 	printf("\n");
	free(key);
	free(value);
	return (result);
}


char	**make_export_fun(char	**export)
{
	int	i;
	char	*str;
	char	**array2d;

	i = 0;
	while (export[i])
	{
		str = print_value_1(export[i]);
		array2d = add_in_split(array2d, str, 0);
		str = free_string(&str);
		i++;
	}
	return (array2d);
}