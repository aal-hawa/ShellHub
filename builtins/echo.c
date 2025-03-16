

# include "../minishell.h"

int	check_echo_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_strlen(str) < 2 || str[0] != '-')
		return (0);
	i = 1;
	while(str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}


char	**echo_n_fun(char **args, int is_print)
{
	char	**result;
	char	*dst;
	int		i;

	if (!*args || !*args)
		return (NULL);
	i = -1;
	dst = NULL;
	result = copy_array2d(&args[2], 0);
	if (!result)
		return (NULL);
	while (result[++i])
	{
		if (result[i + 1])
			dst = join_with_restore(&dst, dst, result[i], " ");
		else
			dst = join_with_restore(&dst, dst, result[i], NULL);
	}
	free_array2d(&result, 0);
	if (!dst)
		dst = ft_strdup("");
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
	if (!result)
		return (NULL);
	while (result[++i])
	{
		if (result[i + 1])
			dst = join_with_restore(&dst, dst, result[i], " ");
		else
			dst = join_with_restore(&dst, dst, result[i], "\n");
	}
	free_array2d(&result, 0);
	if (!dst)
		dst = ft_strdup("\n");
	result = builtins_Message(&dst, is_print, 1);
	if (!is_print)
		free_array2d(&result, 0);
	return (result);
}
