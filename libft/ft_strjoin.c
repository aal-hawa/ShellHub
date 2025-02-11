
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (result == NULL)
		return (NULL);
	if (s1)
		ft_strlcpy(result, s1, s1_len + 1);
	if (s2)
		ft_strlcat(result, s2, s1_len + s2_len + 1);
	return (result);
}
