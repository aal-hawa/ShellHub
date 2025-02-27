
# include "../minishell.h"

char	*value_fun(char *str, char devide_char)
{
	int	i;
	int	y;
	char	*dest;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != devide_char)
		i++;
	if (!str[i] || !str[i + 1])
		return (NULL);
	i++;
	y = ft_strlen(&str[i]);
	dest = malloc(sizeof(char) * (y + 1));
	if (!dest)
		return (NULL);
	y = 0;
	while (str[i])
		dest[y++] = str[i++];
	dest[y] = '\0';
	return (dest);
}

char	*marge_doller_sign(char *str_dollersign, char *str)
{
	char	*dst;
	char	*str_join;

	dst = value_fun(str, ' ');
	if (dst)
	{
		str_join = ft_strjoin(" ", dst);
		dst =ft_restore_value(&dst, &str_join, 1);
		str_join = ft_strjoin(str_dollersign, dst);
		return (str_join);
	}
	return (str_dollersign);
}

char	*Merge_doller_sign(char **str,char **str_sign, t_info *info)
{
	int		i;
	char	*varible;

	i = -1;
	while (info->envp[++i])
	{
		varible = ft_strccpy(info->envp[i], '=');
		if (!varible)
			continue ;
		if (!ft_strcmp(varible, *str_sign))
		{
			*str_sign = free_string(str_sign);
			varible = free_string(&varible);
			*str_sign = marge_doller_sign(value_fun(info->envp[i], '='), *str);
			*str = free_string(str);
			*str = *str_sign;
			return (*str_sign);
		}
		free (varible);
		varible = NULL;
	}
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
	str_sign = Merge_doller_sign(str, &str_sign, info);
	str_sign = free_string(&str_sign);
	str_sign = value_fun(*str, ' ');
	*str = free_string(str);
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
	if (len_split(split_str) < allow_find)
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
		dst = ft_strjoin(dst, split_str[i]);
	free_array2d(&split_str, 0);
	*str = free_string(str);
	*str = dst;
	return (dst);
}
