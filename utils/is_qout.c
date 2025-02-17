#include "../minishell.h"

int	is_qout_fun(int last_is_qout, char c)
{
	if (last_is_qout == 0 && (c == '\"' || c == '\''))
		last_is_qout = 1;
	if (last_is_qout == 1 && (c == '\"' || c == '\''))
		last_is_qout = 0;
	return (last_is_qout);
}