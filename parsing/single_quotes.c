
# include "../minishell.h"

// send char *str from first char after single qoutes
// return NULL if did not have second single qoutes
// return malloc char * between the single qoutes
char	*single_quot_fun(char *str, t_info *info)
{
	char	*dst;

	if (!str)
		return (NULL);
	dst = ft_strccpy(str,  '\'');
	printf("dst0 %s\n", dst);
	if (dst)
		dst = find_doller_sign_fun(&dst, info);
	printf("dst1 %s\n", dst);

	return (dst);
}
