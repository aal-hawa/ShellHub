#include "../minishell.h"

int	is_qout_fun(int last_is_qout, char c)
{
	if (last_is_qout == 0 && c == '\'')
		last_is_qout = 1;
	else if (last_is_qout == 0 && c == '\"')
		last_is_qout = 2;
	else if (last_is_qout == 1 && c == '\'')
		last_is_qout = 0;
	else if (last_is_qout == 2 &&  c == '\"')
		last_is_qout = 0;
	return (last_is_qout);
}