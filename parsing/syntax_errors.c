
# include "../minishell.h"


int	check_error_operators(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		if (is_operator_fun(tokens[i]) > 0
			&& (!tokens[i + 1] || is_operator_fun(tokens[i + 1]) > 0))
			return(1);
		i++;
	}
	return (0);
}