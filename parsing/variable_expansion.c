
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

char	*doller_sign_fun(char **str, t_info *info)
{
	int		i;
	char	*varible;
	char	*str_sign;

	i = -1;
	str_sign = ft_strccpy(*str, ' ');
	if (!str_sign)
		str_sign = ft_strdup(*str);
	while (info->envp[++i])
	{
		varible = ft_strccpy(info->envp[i], '=');
		if (!varible)
			continue ;
		if (!ft_strcmp(varible, str_sign))
		{
			str_sign = free_char(&str_sign);
			str_sign = ft_strjoin(value_fun(info->envp[i], '='), value_fun(*str, ' '));
			*str = free_char(str);
			*str = str_sign;
			return (str_sign);
		}
		free (varible);
		varible = NULL;
	}
	str_sign = free_char(&str_sign);
	*str = free_char(str);
	str_sign = value_fun(*str, ' ');
	if (!str_sign)
		str_sign = ft_strdup("");
	return (str_sign);
}

char	*find_doller_sign_fun(char **str, t_info *info)
{
	char	*dst;
	int		i;
	int		allow_find;
	char **split_str;

	if (!str || !*str)
		return (NULL);
	i = 0;
	dst = NULL;
	allow_find = 2;
	if (str[0][0] == '$')
	{
		i = -1;
		allow_find = 1;
	}
	split_str = ft_split(*str, '$');
	if (len_split(split_str) < allow_find)
	{
		free_split(split_str, 0);
		return (*str);
	}
	while (split_str[++i])
		split_str[i] = doller_sign_fun(&str[i], info);
	i = -1;
	while (split_str[++i])
		dst = ft_strjoin(dst, split_str[i]);
	free_split(split_str, 0);
	*str = free_char(str);
	*str = dst;
	printf ("dst %s\n", dst);
	return (dst);
}
