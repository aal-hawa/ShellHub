#include "../minishell.h"

char	*ft_strjoin_path(char const *s1, char const *s2, int is_path)
{
	size_t	len;
	char	*dst;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (len + 2));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
		dst[j++] = s1[i++];
	if (is_path == 1)
		dst[j++] = '/';
	i = 0;
	while (s2 && s2[i])
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}
