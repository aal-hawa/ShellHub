
#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void) av;
	(void) envp;
	if (ac == 1)
		minishell();
	else
		return (1);
	return (0);
}
