
#include "../minishell.h"
// return length of string before to_char
// return 0 if did not have to_char inside the string
// return -1 if the to_char is the first index
ssize_t	ft_strclen(const char *s, char to_char)
{
	ssize_t	i;

	i = 0;
	while (s[i] && s[i] != to_char)
		i++;
	if (!s[i])
		return (0);
	if (i == 0)
		i = -1;
	return (i);
}