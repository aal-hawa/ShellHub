/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_line_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:23:20 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:21 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_more_spaces(char **line)
{
	int	i;
	int	j;
	int	is_qout;

	if (!line || !*line)
		return (0);
	i = 0;
	j = 0;
	is_qout = 0;
	while (line[0][i])
	{
		if (is_qout == 0 && line[0][i] == '\t')
			line[0][i] = ' ';
		if (i != 0 && is_qout == 0 && is_char_operator_fun(line[0][i])
			&& line[0][i - 1] != ' ' && line[0][i - 1] != line[0][i])
			j++;
		if (is_qout == 0 && is_char_operator_fun(line[0][i]) && line[0][i
			+ 1] != ' ' && line[0][i + 1] != line[0][i])
			j++;
		is_qout = is_qout_fun(is_qout, line[0][i]);
		i++;
	}
	return (j);
}

char	*fill_new_string(char **line, int len)
{
	char	*dst;
	int		i;
	int		j;
	int		is_qout;

	i = -1;
	j = 0;
	is_qout = 0;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	while (line[0][++i])
	{
		if (i != 0 && is_qout == 0 && i != 0 && is_char_operator_fun(line[0][i])
			&& line[0][i - 1] != ' ' && line[0][i - 1] != line[0][i])
			dst[j++] = ' ';
		dst[j++] = line[0][i];
		if (is_qout == 0 && is_char_operator_fun(line[0][i]) && line[0][i
			+ 1] != ' ' && line[0][i + 1] != line[0][i])
			dst[j++] = ' ';
		is_qout = is_qout_fun(is_qout, line[0][i]);
	}
	dst[j] = '\0';
	return (dst);
}

void	fixed_line_spaces(char **line)
{
	int		len;
	char	*dest;

	if (!line || !*line)
		return ;
	len = add_more_spaces(line);
	if (len == 0)
		return ;
	len += strlen(*line);
	printf("len %d\n", len);
	dest = fill_new_string(line, len);
	printf("strlen dest %ld\n", strlen(dest));
	*line = free_string(line);
	*line = dest;
}
