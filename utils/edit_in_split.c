
#include "../minishell.h"

int	is_exist_str_in_2array(char **array2d, char *del_str)
{
	int		i;
	
	i = -1;
	while (array2d && array2d[++i])
	{
		if (!ft_strccmp(array2d[i], del_str, '='))
			return (i);
	}
	return (-1);
}
int	len_array2d(char **array2d)
{
	int	len;

	len = 0;
	if (!array2d)
		return (len);
	while (array2d[len])
		len++;
	return (len);
}

char	**copy_export_env(char **array2d)
{
	int	i;
	int	len;
	char	**new_array2d;

	i = 0;
	if (!array2d)
		return (NULL);
	len = len_array2d(array2d);
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (i < len)
	{
		new_array2d[i] = NULL;
		new_array2d[i] = ft_join_with_restore(&new_array2d[i], array2d[i], "\n", NULL);
		i++;
	}
	new_array2d[i] = NULL;
	return (new_array2d);
}

char	**copy_array2d(char **array2d)
{
	int	i;
	int	len;
	char	**new_array2d;

	i = 0;
	if (!array2d)
		return (NULL);
	len = len_array2d(array2d);
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (i < len)
	{
		new_array2d[i] = ft_strdup(array2d[i]);
		i++;
	}
	new_array2d[i] = NULL;
	return (new_array2d);
}

char	*ft_add_qout_export(char **str)
{
	int	i;
	int	j;
	int	len;
	char	*new_str;
	int	is_got_equal;
	
	len = strlen(*str);
	new_str = malloc(sizeof(char) * (len + 3));
	i = -1;
	is_got_equal = 0;
	j = 0;
	if (!new_str)
		return (NULL);
	while (str[0][++i])
	{
		new_str[j++] = str[0][i];
		if (is_got_equal == 0 && str[0][i] == '=')
		{
			new_str[j++] = '\"';
			is_got_equal = 1;
		}
	}
	if (is_got_equal == 1)
		new_str[j++] = '\"';
	new_str[j] = '\0';
	*str = free_string(str);
	*str = new_str;
	return (*str);
}

char	**copy_array2d_export(char **array2d)
{
	int	i;
	int	len;
	char	**new_array2d;

	i = 0;
	if (!array2d)
		return (NULL);
	len = len_array2d(array2d);
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (i < len)
	{
		new_array2d[i] = NULL;
		new_array2d[i] = ft_join_with_restore(&new_array2d[i], "declare -x ", array2d[i], NULL);
		new_array2d[i] = ft_add_qout_export(&new_array2d[i]);
		i++;
	}
	new_array2d[i] = NULL;
	return (new_array2d);
}

// check if you want share adress of split three pointers
char	**del_str_from_array2d(char ***array2d, char *del_str)
{
	int		i;
	int		y;
	int		len;
	char	**new_array2d;
	int		z;

	z = is_exist_str_in_2array(*array2d, del_str);
	if ( z == -1)
		return (*array2d); 
	i = -1;
	y = -1;
	len = len_array2d(*array2d);
	new_array2d = malloc(sizeof(char *) * (len));
	if (!new_array2d)
		return (NULL);
	while (array2d[0][++i])
	{
		if (i != z)
			new_array2d[++y] = ft_strdup(array2d[0][i]);
	}
	new_array2d[++y] = NULL;
	free_array2d(array2d, len);
	return (new_array2d);
}

char	**add_in_array2d(char ***array2d, char *add_str, int is_alpha)
{
	int		i;
	int		j;
	int		len;
	char	**new_array2d;

	i = 0;
	j = 0;
	len = len_array2d(*array2d) + 1;
	new_array2d = malloc(sizeof(char *) * (len + 1));
	if (!new_array2d)
		return (NULL);
	while (*array2d && array2d[0][i])
	{
		if (is_alpha == 1 && ft_strcmp(array2d[0][i], add_str) && is_alpha++)
			new_array2d[j++] = ft_strdup(add_str);
		else
			new_array2d[j++] = ft_strdup(array2d[0][i++]);
	}
	if (!*array2d || is_alpha < 2)
		new_array2d[j++] = ft_strdup(add_str);
	new_array2d[j] = NULL;
	free_array2d(array2d, len - 1);
	return (new_array2d);
}

char	**merge_2_arrays2d(char ***first_array2d, char ***second_array2d)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	**new_array2d;

	i = 0;
	len1 = len_array2d(*first_array2d);
	len2 = len_array2d(*second_array2d);
	new_array2d = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!new_array2d)
		return (NULL);
	while (*first_array2d && first_array2d[0][i])
	{
		new_array2d[i] = ft_strdup(first_array2d[0][i]);
		i++;
	}
	j = 0;
	while (*second_array2d && second_array2d[0][j])
		new_array2d[i++] = ft_strdup(second_array2d[0][j++]);
	new_array2d[i] = NULL;
	free_array2d(first_array2d, len1);
	free_array2d(second_array2d, len2);
	return (new_array2d);
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
}

char	*ft_join_with_restore(char	**dst, char *s1, char *s2, char *s3)
{
	char	*str_join;

	str_join = ft_strjoin(s1, s2);
	*dst = ft_restore_value(dst, &str_join, 1);
	if (s3)
	{
		str_join = ft_strjoin(*dst, s3);
		*dst = ft_restore_value(dst, &str_join, 1);
	}
	return (*dst);
}

char	*print_value_1(char *arg)
{
	int		i;
	char	*key;
	char	*value;
	char	*result;

	i = 0;
	result = NULL;
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
	result = ft_join_with_restore(&result, "declare -x ",key, NULL);
	if (value)
	{
		result = ft_join_with_restore(&result, result, "=", NULL);
		add_double_quotes_1(&value);
		result = ft_join_with_restore(&result, result, value, NULL);
	}
	result = ft_join_with_restore(&result, result, "\n", NULL);
	free(key);
	free(value);
	return (result);
}


char	**make_export_fun(char **export)
{
	int	i;
	char	*str;
	char	**array2d;

	i = 0;
	array2d = NULL;
	while (export[i])
	{
		str = print_value_1(export[i]);
		array2d = add_in_array2d(&array2d, str, 0);
		str = free_string(&str);
		i++;
	}
	return (array2d);
}
