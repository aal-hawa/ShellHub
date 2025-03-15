
# include "../minishell.h"

char	*free_string(char **this_string)
{
	if (!this_string || !*this_string)
		return (NULL);
	free(*this_string);
	*this_string = NULL;
	return (NULL);
}

// char	*while_next_line(char **text_buffer, ssize_t bytesreed, int *is_done,
// 		t_info *info)
// {
// 	char	returntext[2];

// 	while (1)
// 	{
// 		bytesreed = read(0, returntext, 1);
// 		if (bytesreed > 0)
// 		{
// 			returntext[bytesreed] = '\0';
// 			*text_buffer = (*text_buffer, returntext, is_done,
// 					info);
// 			if (*is_done == 1)
// 				break ;
// 		}
// 	}
// 	return (*text_buffer);
// }

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
		if (is_done == 1)
			break ;
	}
	return (text_buffer);
}
