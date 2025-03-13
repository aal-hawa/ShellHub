

#include "../minishell.h"

static int	is_has_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

static char **add_to_env(char **arr, char *arg)
{
	if (is_exist_str_in_2array(arr, arg, 0))
	{
		arr = del_str_from_array2d(&arr, arg);
		arr = add_in_array2d(&arr, arg, 0);
	}
	else
	{
		arr = add_in_array2d(&arr, arg, 1);
	}
	return (arr);
}

static int check_valid_args(char **arr)
{
	int	i;

	i = 1;
	while(arr[i])
	{
		if(!is_has_equal(arr[i]))
		{
			printf("env: %s: No such file directly\n", arr[i]);
			return(0);
		}
		i++;
	}
	return (1);
}

static void print_env(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		printf("%s\n", arr[i++]);
}

char	**env_fun(char **args, t_info * info, int is_print)
{
	int i = 1;
	char **cpy_print = NULL;
	cpy_print = copy_array2d(info->envp);
	if(args[i])
	{
		if(!check_valid_args(args))
			return (NULL);
		else
		{
			while(args[i])
				cpy_print = add_to_env(cpy_print, args[i++]);
		}
	}
	if(is_print)
		print_env(cpy_print);
	env_data(info);
	return (cpy_print);
}
