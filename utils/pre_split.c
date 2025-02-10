/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aal-hawa <aal-hawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 13:46:30 by tmahmoud          #+#    #+#             */
/*   Updated: 2025/02/09 20:35:25 by aal-hawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t new_len(const char *s, const char *ops)
{
    size_t new_len = 0;
    size_t i = 0;
    size_t j;

    while (s[i])
    {
        new_len++;
        j = 0;
        while (ops[j])
        {
            if (s[i] == ops[j])
            {
                new_len += 2;
                break;
            }
            j++;
        }
        i++;
    }
    return (new_len);
}
 
static int is_operator(const char c, const char *ops)
{
    size_t j = 0;
    while (ops[j])
    {
        if (c == ops[j])
        {
            return (1);
        }
        j++;
    }
    return (0);
}

static void replace_fct(char *result, size_t k, char c, int duble)
{
    if(duble)
    {   
        result[k++] = ' ';
        result[k++] = c;
        result[k++] = c;
        result[k++] = ' ';
    }
    else
    {
        result[k++] = ' ';
        result[k++] = c;
        result[k++] = ' ';
    }
}

static char *get_result(const char *s, const char *ops, char *result)
{
    size_t i = 0;
    size_t k = 0;

    while (s[i])
    {
        if (is_operator(s[i], ">") && is_operator(s[i + 1], ">"))
        {
            replace_fct(result, k, '>', 1);
            i++;
        }
        else if (is_operator(s[i], "<") && is_operator(s[i + 1], "<"))
        {
            result[k++] = ' ';
            result[k++] = '<';
            result[k++] = '<';
            result[k++] = ' ';
            i++;
        }
        else if (is_operator(s[i], ops))
        {
            result[k++] = ' ';
            result[k++] = s[i];
            result[k++] = ' ';
        }
        else
        {
            result[k++] = s[i];
        }
        i++;
    }
    result[k] = '\0';
    return (result);
}

char *pre_split(char **s, const char *ops)
{
    size_t len = new_len(*s, ops);
    char *result = malloc(len + 1);
    if (!result)
    {
        perror("malloc failed");
        return NULL;
    }
    result = get_result(*s, ops, result);
    free(*s);
    *s = NULL;
    return (result);
}
