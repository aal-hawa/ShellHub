#include "minishell.h"

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\nshellhub$ ", 12);
}

void sigquit_handler(int sig)
{
    (void)sig;
}

void setup_signals(void)
{
    signal(SIGINT, sigint_handler);  // Ctrl-C: Show new prompt
    signal(SIGQUIT, sigquit_handler); // Ctrl-\: Do nothing
}

int	main(int ac, char **arg, char **envp)
{
	setup_signals();
	(void) arg;
	// (void) envp;
	char	*env;
	t_info	info;
	t_colors	colors;

	if (ac == 1)
	{
		env_data(envp, &env, &info);
		init_colors(&colors, &info);
		init_info(ac, env, envp, &info); // make it before env_data()
		if (!env)
			info.env_null = 1;
		minishell(&info);
	}
	else
		return (1);
	return (0);
}
