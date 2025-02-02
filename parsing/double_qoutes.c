
# include "../minishell.h"

// send str from first char after double qoutes
// return NULL if did not have second double qoutes
// return dest between the double qoutes
char *double_quot_fun(char *str)
{
	return (ft_strccpy(str,  '\"'));
}
