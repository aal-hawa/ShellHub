#include "minishell.h"

int	main(int ac, char **arg, char **envp)
{
	(void) arg;
	// (void) envp;
	char	*env;
	t_info	info;
	t_colors	colors;

	if (ac == 1)
	{
		env_data(envp, &env, &info);
		init_colors(&colors, &info);
		init_info(ac, env, envp, &info);
		if (!env)
			info.env_null = 1;
		minishell(&info);
	}
	else
		return (1);
	return (0);
}
