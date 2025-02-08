
# include "../minishell.h"

int	is_operator_fun(char *str)
{
	if (ft_strcmp(str, "|") || ft_strcmp(str, ">")
		|| ft_strcmp(str, "<")
		|| ft_strcmp(str, ">>") || ft_strcmp(str, "<<"))
		return (1);
	return (0);
}