
#include "../minishell.h"

// copy char *str to first char of char to_char
// if didnt have the char to_char inside the char *str it will return NULL
// if have it will return malloc char	*
char *ft_strccpy(char *str, char to_char)
{
	char	*dest;
	ssize_t	i;

	if (!str)
		return (NULL);
	i = ft_strclen(str, to_char);
	if (i == 0)
		return (NULL);
	if (i == -1)
		return (ft_strdup(""));
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

/*copy char *str (send adress of the str) to first char of char to_char
if didnt have the char to_char inside the char *str it didnt do any thing
if have it will free the last value and put a new value char	*
it is do the same idia function ft_strccpy but it is free the last value */
void	ft_strccpy_free(char **str, char to_char)
{
	char	*dest;
	ssize_t	i;

	if (!str || !*str)
		return ;
	i = ft_strclen(*str, to_char);
	if (i == 0)
		return ;
	if (i == -1)
	{
		dest = ft_strdup("");
		*str = free_char(str);
		*str = dest;
		return ;
	}
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return ;
	ft_strlcpy(dest, *str, i);
	*str = free_char(str);
	*str = dest;
}
