/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_wr_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:22:46 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/03/17 17:22:49 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file_r(char *name_file)
{
	int	fd;

	fd = open(name_file, O_RDONLY, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_w(char *name_file)
{
	int	fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_w_b(char *name_file)
{
	int	fd;

	fd = open(name_file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}

int	open_file_r_w(char *name_file)
{
	int	fd;

	fd = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		perror(name_file);
	return (fd);
}
