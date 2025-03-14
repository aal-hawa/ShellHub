

# include "../minishell.h"

char	**echo_n_fun(char **args, int is_print)
{
	char	**result;

	if (!*args || !*args)
		return (NULL);
	result = copy_array2d(&args[2], 0);
	if (!result)
		return (NULL);
	if (is_print == 1)
		print_array2d(result, 0);
	return (result);
}

char	**echo_with_line_fun(char **args, int is_print)
{

	char	**result;

	if (!*args || !*args)
		return (NULL);
	result = copy_array2d(&args[1], 1);
	if (!result)
		return (NULL);
	if (is_print == 1)
		print_array2d(result, 0);
	return (result);
}
