
# include "../minishell.h"

char *readline_fun()
{
	char *line;
	
	line = readline ("Enter a line: ");
	add_history(line);
	return (line);
}