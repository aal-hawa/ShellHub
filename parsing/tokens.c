
# include "../minishell.h"

char **tokens_fun(char *line)
{
	line = pre_split(&line, "|<>");
	char **split;
	split = ft_split(line, ' ');
	return (split);	
}