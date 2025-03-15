
# include "../minishell.h"

int	last_letters(char *str, int *is_done, t_info *info)
{
	int	j;

	j = ft_strlen(str) - info->i_limiter;
	if (j < 0)
		return (0);
	if (!ft_strcmp(&str[j], info->limiter))
	{
		if (j == 0 || str[j - 1] == '\n')
			return (is_done[0] = 1, 1);
	}
	return (0);
}

char	*strjoin_herdoc(char **s1, char *s2, int *is_done, t_info *info)
{
	size_t	len;
	char	*dst;
	size_t	i;
	size_t	j;

	len = ft_strlen(*s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 2));
	i = 0;
	j = 0;
	if (!dst)
		return (NULL);
	while (*s1 && s1[0][i])
		dst[j++] = s1[0][i++];
	i = 0;
	while (s2 && s2[i])
		dst[j++] = s2[i++];
	dst[j++] = '\n';
	dst[j] = '\0';
	*s1 = free_string(s1);
	if (last_letters(dst, is_done, info) == 1)
		while (info->i_limiter-- >= 0)
			dst[j--] = '\0';
	return (dst);
}
