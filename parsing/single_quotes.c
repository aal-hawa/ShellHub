
# include "../minishell.h"

// send char *str from first char after single qoutes
// return NULL if did not have second single qoutes
// return malloc char * between the single qoutes
char	*single_quot_fun(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strccpy(str,  '\''));
}
