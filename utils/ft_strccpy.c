
#include "../minishell.h"

// copy str to char
char *ft_strccpy(char *str, char to_char)
{
	char	*dest;
	size_t	i;

	i = ft_strclen(str, to_char);
	if (i == 0)
		return (NULL);
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != to_char)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
