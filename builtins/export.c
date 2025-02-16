/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:45:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/16 17:41:41 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"


int check_is_valide(char *str)
{
	int i = 0;
	if(!((str[0] >=  65 && str[0] <= 90) || (str[0] >=  97 && str[0] <= 122) || str[0] == '_'))
		return (0);
	while(str[i])
	{
			
	}
}

char	**export_fun(char **args, t_info *info, int is_print)
{
	int i = 0;
	//delete (void) when create the function
	(void)is_print;
	if (!info)
		return (NULL);
	while(args[i])
    {
     	printf("from export =[%d]=> here is the args: %s \n", i, args[i]);
		i++;
    }
// int i = 0;
    // if(!name)
    // {
    //  printf("print export output\n");
    //  return (1);
    // }
    // else
    // {
    //  printf("from export => here is the name: %s\n", name);
    //  args = ft_split(name, ' ');
    //  printf("here is arg[1]: %s\n", args[1]);
    //  // while(args[i])
    //  // {
    //  // printf("from export => here is the args: %s \n", args[i++]);
    //  // }
    // }

	
	// if (!getenv(args))
	// {
	// 	info->envp = add_in_split(info->envp, args, 1);
	// 	return (0);
	// }
	return (NULL);
}