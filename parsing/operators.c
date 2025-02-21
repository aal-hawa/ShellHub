
# include "../minishell.h"

// return zero if not, two if pipe, one if else operators
int	is_operator_fun(char *str)
{
	if (!str)
		return (0);
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, ">")
		|| !ft_strcmp(str, "<")
		|| !ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
	{
		if (!ft_strcmp(str, "|"))
			return (2);
		else
			return (1);
	}
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
	{
		printf("\n-----------------------------ERROR-----------------------------\n");
		return (0);
	}
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>"))
		return (1);
	return (0);
}

int	is_char_operator_fun(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}
