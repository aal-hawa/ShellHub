
# include "../minishell.h"

// send str from first char after single qoutes
// return NULL if did not have second single qoutes
// return dest between the single qoutes
char *single_quot_fun(char *str)
{
		return (ft_strccpy(str,  '\''));
}
