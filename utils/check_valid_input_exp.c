#include "../minishell.h"

int	check_valid_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int	check_valid_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_is_valid_key(char *str)
{
	int	i;

	if (!str || str[0] == '\0' || !check_valid_alpha(str[0]))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!(check_valid_alpha(str[i]) || check_valid_num(str[i])))
			return (0);
		i++;
	}
	return (1);
}