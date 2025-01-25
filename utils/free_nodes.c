/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 19:58:17 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/01/25 16:04:13 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_nodes(t_node *head)
{
    t_node *temp;
    while (head) {
        temp = head;
        head = head->next;
        if (temp->args) {
            for (int i = 0; temp->args[i]; i++)
                free(temp->args[i]);
            free(temp->args);
        }
        free(temp);
    }
}
