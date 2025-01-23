/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:47:16 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/23 17:15:21 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/libft.h"

typedef struct s_node {
    char **args;
    char type;
    struct s_node *next;
} t_node;


typedef struct s_info
{
	char	**env;
    int     status_exit;
    char    *curent_path;
}					t_info;

void	minishell();
char	*readline_fun();
char	**tokens_fun(char *line);
char	*cd_fun(char *cd, t_info *info);
char	*pwd_fun(t_info *info);
void	exit_fun();
void	echo_n_fun(char *str);
void    free_nodes(t_node *head);
int     is_operator_fun(char *str);
void	free_fun(char **str);
#endif