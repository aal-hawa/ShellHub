
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
	int	i;
	char	*varible;

	i = 0;
	while (info->envp[i])
	{
		varible = ft_strccpy(info->envp[i], '=');
		if (!varible)
		{
			i++;
			continue ;
		}
		if (varible == *(str + 1))
		{
			*str = free_char(str);
			return (value_fun(info->envp[i], '='));
		}
		free (varible);
		varible = NULL;
		i++;
	}
	*str = free_char(str);
	return (ft_strdup(""));
}

char	*find_doller_sign_fun(char **str, t_info *info)
{
	char	*dst;
	int		i;
	char **split_str;

	if (!str || !*str)
		return (NULL);
	i = 0;
	dst = NULL;
	split_str = ft_split(*str, '$');
	if (len_split(split_str) < 2)
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
	return (dst);
}
