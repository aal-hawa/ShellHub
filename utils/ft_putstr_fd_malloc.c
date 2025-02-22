#include "../minishell.h"

void	ft_putstr_fd_malloc(char *s, int fd, int is_malloc)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (is_malloc == 2 || is_malloc -1)
		write(fd, "\n", 1);
	if (is_malloc == 1 || is_malloc == 2)
		free_char(&s);
}