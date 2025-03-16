
# include "../minishell.h"

char	*value_fun(char *str, char devide_char)
{
	int	i;
	
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != devide_char)
		i++;
	if (!str[i] || !str[i + 1])
		return (NULL);
	i++;
	return (ft_strdup(&str[i]));
}

char	*merge_result_with_after_space(char *str_dollersign, char *str)
{
	char	*after_space;
	char	*dst;

	after_space = value_fun(str, ' ');
	dst = NULL;
	if (after_space)
	{
		dst = join_with_restore(&dst, str_dollersign," ", after_space);
		after_space = free_string(&after_space);
		return (dst);
	}
	return (str_dollersign);
}

char	*merge_doller_sign(char **str, char **str_sign, t_info *info)
{
	int		i;
	char	*value;

	value = NULL;
	i = is_exist_str_in_2array(info->envp, *str_sign);
	if (i > -1)
	{
		*str_sign = free_string(str_sign);
		value = value_fun(info->envp[i], '=');
		*str_sign = merge_result_with_after_space(value, *str);
		*str = ft_restore_value(str, str_sign, 1);
		return (*str);
	}
	*str_sign = free_string(str_sign);
	*str_sign = merge_result_with_after_space(value, *str);
	return (*str_sign);
}

char	*doller_sign_fun(char **str, t_info *info)
{
	char	*str_sign;

	if (ft_strlen(*str) == 0)
		return ft_strdup("$");
	if (str[0][0] == '?')
		return (status_program_fun(str, info));
	str_sign = ft_strccpy(*str, ' ');
	if (!str_sign)
		str_sign = ft_strdup(*str);
	str_sign = merge_doller_sign(str, &str_sign, info);
	if (!str_sign)
		str_sign = ft_strdup("");
	return (str_sign);
}

char	**split_by_doller_sign(char **str, int *i)
{
	int		allow_find;
	char	**split_str;

	*i = 0;
	allow_find = 2;
	if (str[0][0] == '$')
	{
		*i = -1;
		allow_find = 1;
	}
	split_str = ft_split(*str, '$');
	if (len_array2d(split_str) < allow_find)
	{
		free_array2d(&split_str, 0);
		return (NULL);
	}
	return (split_str);
}

char	*find_doller_sign_fun(char **str, t_info *info)
{
	char	*dst;
	int		i;
	char	**split_str;

	if (!str || !*str)
		return (NULL);
	i = 0;
	dst = NULL;
	split_str = split_by_doller_sign(str, &i);
	if (!split_str)
		return (*str);
	while (split_str[++i])
		split_str[i] = doller_sign_fun(&split_str[i], info);
	i = -1;
	while (split_str[++i])
		dst = join_with_restore(&dst, dst, split_str[i], NULL);
	free_array2d(&split_str, 0);
	*str = free_string(str);
	*str = dst;
	return (dst);
}
