
# include "../minishell.h"

char *readline_fun()
{
	char *line;
	
	line = readline ("shellhub$ ");
	add_history(line);
	return (line);
}
