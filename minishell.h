/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:47:16 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/01/21 19:59:38 by tmahmoud         ###   ########.fr       */
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
}					t_info;

void	minishell();
char	*readline_fun();
char	**tokens_fun(char *line);
char	*cd_func(char *cd);
char	*pwd_func();
void	exit_func();
void	echo_func(char *str);
void free_nodes(t_node *head);
#endif