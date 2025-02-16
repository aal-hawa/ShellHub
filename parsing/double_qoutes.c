
# include "../minishell.h"

// send char *str from first char after double qoutes
// return NULL if did not have second double qoutes
// return malloc char * between the double qoutes
char	*double_quot_fun(char *str)
{
	if (!str)
		return (NULL);
	return (ft_strccpy(str,  '\"'));
}
