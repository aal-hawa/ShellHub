
#include "minishell.h"
// ls | grep "txt"
void	minishell(void)
{
	char	*line;
	char **tokens;

	while (1)
	{
		// char **tokens;
		// readLine && hestory
		line = readline_fun();
		printf("the input: %s\n", line);
		tokens = tokens_fun(line);
		while(*tokens)
			printf("the tokens: %s\n", *tokens++);
		free(line);
		// nodes
		// syntax error
		// commands structure
	}
}
