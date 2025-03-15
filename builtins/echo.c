

# include "../minishell.h"

char	**echo_n_fun(char **args, int is_print)
{
	char	**result;
	char	*dst;
	int		i;

	if (!*args || !*args)
		return (NULL);
	i = -1;
	dst = NULL;
	result = copy_array2d(&args[1], 0);
	while (result[++i])
	{
		if (result[i + 1])
			dst = ft_join_with_restore(&dst, dst, result[i], " ");
		else
			dst = ft_join_with_restore(&dst, dst, result[i], NULL);
	}
	if (!result)
		return (NULL);
	free_array2d(&result, 0);
	result = builtins_Message(&dst, is_print, 1);
	if (!is_print)
		free_array2d(&result, 0);
	return (result);
}

char	**echo_with_line_fun(char **args, int is_print)
{
	char	**result;
	char	*dst;
	int		i;

	if (!*args || !*args)
		return (NULL);
	i = -1;
	dst = NULL;
	result = copy_array2d(&args[1], 0);
	while (result[++i])
	{
		if (result[i + 1])
			dst = ft_join_with_restore(&dst, dst, result[i], " ");
		else
			dst = ft_join_with_restore(&dst, dst, result[i], "\n");
	}
	if (!result)
		return (NULL);
	free_array2d(&result, 0);
	result = builtins_Message(&dst, is_print, 1);
	if (!is_print)
		free_array2d(&result, 0);
	return (result);
}
