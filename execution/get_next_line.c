
# include "../minishell.h"

char	*free_string(char **this_string)
{
	if (!this_string || !*this_string)
		return (NULL);
	free(*this_string);
	*this_string = NULL;
	return (NULL);
}

char	*get_next_line(t_info *info)
{
	char	*text_buffer;
	char	*returntext;
	int		is_done;

	is_done = 0;
	text_buffer = NULL;
	while (1)
	{
		returntext = readline("> ");
		text_buffer = strjoin_herdoc(&text_buffer, returntext, &is_done, info);
		returntext = free_string(&returntext);
		if (is_done == 1)
			break ;
	}
	return (text_buffer);
}
