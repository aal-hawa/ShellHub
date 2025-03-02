

# include "../minishell.h"

void	exit_number(int exit_status, t_info * info)
{
	unlink_files(info);
	free_info(info);
	exit (exit_status);
}
void	exit_fun(char **arg, t_info *info)
{
	int	status_exit;
	int	i;
	if (!arg[1])
		exit_number(0, info);
	i = -1;
	if (len_split(arg) > 2)
	{
		while (arg[1][++i])
		{
			if (!ft_isdigit(arg[1][i]))
			{
				builtins_error_message("exit", arg[1]);
				exit_number(255, info);
			}
		}
		printf("bash: exit: too many arguments\n");
		return ;
	}
	if (!ft_isdigit(arg[1][0]))
		exit_number(2, info);
	status_exit = ft_atoi(arg[1]);
	// free all things before exit program
	exit_number(status_exit % 256, info);
}

