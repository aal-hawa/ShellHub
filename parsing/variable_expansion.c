
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
		if (varible == *str)
		{
			*str = free_char(str);
			return (value_fun(info->envp[i], '='));
		}
		free (varible);
		varible = NULL;
		i++;
	}
	*str = free_char(str);
	return (NULL);
}

char	*find_doller_sign_fun(char **str, t_info *info)
{
	char	*dst;
	// char	*result;
	int		i;
	int		j;
	int		len;

	if (!str || !*str)
		return (NULL);
	i = 0;
	j = 0;
	dst = NULL;
	// result = NULL;
	while (str[i])
	{
		if (str[0][i] == '$')
		{
			j++;
			i++;
			while(str[0][i] && (str[0][i] != '$' || str[0][i] != ' '))
			{
				j++;
				i++;
			}
			dst = malloc(sizeof(char) * (i - j + 1));
			ft_strlcat(dst, str[i], j);
			dst = doller_sign_fun(&dst, info);
			if (dst)
			{
				len = strlen(dst);
				len += i - j;
				
			}
		}

	}
	return (NULL);
}
