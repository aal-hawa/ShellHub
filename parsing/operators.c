
# include "../minishell.h"

int	is_operator_fun(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

int	is_operator_input_fun(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

int	is_operator_output_fun(char *str)
{
	if (!str)
	return (0);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}