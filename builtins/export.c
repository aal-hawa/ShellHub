/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmahmoud <tmahmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:45:13 by aal-hawa          #+#    #+#             */
/*   Updated: 2025/02/18 17:25:02 by tmahmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int check_valid_alpha_(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (1);
	return (0);
}

int check_valid_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int check_is_valid(char *str)
{
	int i = 1;

	if (!str || str[0] == '\0' || !check_valid_alpha_(str[0]))
		return (0);
	while (str[i])
	{
		if (!(check_valid_alpha_(str[i]) || check_valid_num(str[i]) || str[i] == '='))
			return (0);
		i++;
	}
	return (1);
}

//export hello from 42AD We @re So H@ppy here live here=everything USER

int is_env(char *str)
{
	while(*str)
	{
		if(*str == '=')
			return(1);
		str++;
	}
	return (0);
}

void check_and_add(t_info *info, char *arg, int add_to_env)
{
	(void) add_to_env;
	if(is_exist_str_in_2array(info->export, arg, 0) || is_exist_str_in_2array(info->export, arg, ft_strlen(arg)))
	{
		info->export = del_str_from_array2d(info->export, arg, ft_strlen(arg));
		info->export = add_in_split(info->export, arg, 0);
		printf("\n------\ndeleting {{%s}}, adding with new value{{%s}}\n------\n", arg, arg);
		// if(add_to_env &&(is_exist_str_in_2array(info->envp, arg, 0) || is_exist_str_in_2array(info->envp, arg, ft_strlen(arg))))
		// {
		// 	info->envp = del_str_from_array2d(info->envp, arg, 0);
		// 	info->envp = add_in_split(info->envp, arg, 0);
		// } 
		// else
		// {
		// 	info->envp = add_in_split(info->envp, arg, 0);
		// }
		//delete
		//add
	}
	else
	{
		info->export = add_in_split(info->export, arg, 1);
		if(add_to_env)
			info->envp = add_in_split(info->envp, arg, 0);
		printf("\n------\nadding{{%s}}\n------\n",arg);
		//add
	}
}

void print_export(t_info *info)
{
	int i = 0;
	
	while(info->export[i])
	{
		printf("%s\n", info->export[i++]);
	}
}

char	**export_fun(char **args, t_info *info, int is_print)
{
	int i = 1;
	//delete (void) when create the function
	(void)is_print;
	if (!info)
		return (NULL);
    if(!args[i])
    {
     print_export(info);
    }
	while (args[i])
	{
		if (check_is_valid(args[i]))
		{
			printf("\n\nValid str: %s \n\n", args[i]);
			if(is_env(args[i]))
			{
				printf("Add to env\n");
				check_and_add(info, args[i], 1);
			}	
			else
			{
				check_and_add(info, args[i], 0);
				printf("Don't add to env\n");
			}
		}
		else
			printf("\nNot Valid str: %s\n", args[i]);
		i++;
	}

	return (NULL);
}
