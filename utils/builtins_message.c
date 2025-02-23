
#include "../minishell.h"

char	*builtins_error_message(char *str_tybe_builtins, char *str_input)
{
	char	*str_message;
	char	*result;

	str_message = ft_strjoin("bash: ", str_tybe_builtins);
	result = ft_strjoin(str_message, ": ");
	str_message = ft_restore_value(&str_message, &result, 1);
	result = ft_strjoin(str_message, str_input);
	str_message = ft_restore_value(&str_message, &result, 1);
	result = ft_strjoin(str_message, ": No such file or directory\n");
	str_message = ft_restore_value(&str_message, &result, 1);
	return (str_message);
}
// if is malloc = 1, that's mean I wanna free it
char	**builtins_Message(char **str_massege, int is_print, int is_malloc)
{
	char	**result;

	if (is_print == 1)
		printf ("%s", *str_massege);
	result = malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(*str_massege);
	result[1] = NULL;
	if (is_malloc == 1)
		*str_massege = free_char(str_massege);
	return (result);
}
