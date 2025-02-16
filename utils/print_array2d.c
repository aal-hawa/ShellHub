#include "../minishell.h"

void	print_array2d(char **array2d)
{
	int	i;

	i = 0;
	while(array2d[i])
		printf("%s\n", array2d[i++]);
}

void	print_array2d_fd(char **array2d, int fd)
{
	int	i;

	i = 0;
	if (!array2d)
	{
		printf("\n---------------------------ERROR---------------------------\n");
		return ;
	}
	while(array2d[i])
		ft_putstr_fd(array2d[i++], fd);
}