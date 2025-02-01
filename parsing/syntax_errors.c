
# include "../minishell.h"


int	check_error_operators(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is_operator_fun(tokens[i]) == 1
			&& (!tokens[i + 1] || is_operator_fun(tokens[i + 1]) == 1))
			return(1);
		i++;
	}
	return (0);
}