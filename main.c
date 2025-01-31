
#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	// (void) envp;
	char	*env;
	t_info	info;
	if (ac == 1)
	{
		env_data(envp, &env, &info);
		init_info(ac, env, envp, &info);
		minishell();
	}
	else
		return (1);
	return (0);
}
