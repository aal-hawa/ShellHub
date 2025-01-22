/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:58:17 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/22 19:16:21 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_nodes(t_node *head)
{
    t_node *temp;
    int i;

    while (head)
    {
        temp = head;
        head = head->next;
        if (temp->args) {
            i = 0;
            while (temp->args[i])
                free(temp->args[i++]);
            free(temp->args);
        }
        free(temp);
    }
}
