
# include "../minishell.h"

int	is_operator_fun(char *str)
{
	if (ft_memcmp(str, "|", 1) || ft_memcmp(str, ">", 1)
		|| ft_memcmp(str, "<", 1)
		|| ft_memcmp(str, ">>", 2) || ft_memcmp(str, "<<", 2))
		return (1);
	return (0);
}