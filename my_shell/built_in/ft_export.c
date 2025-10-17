/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:14:45 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:05 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**  -1 : not valid
**   0 : only var
**   1 : var and value
**   2 : + value
*/
int	valid_case(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '=' || str[i] == 0)
	{
		return (-1);
	}
	if (ft_isdigit(str[i]) == 1)
		return (-1);
	while (str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (2);
			else if (str[i] == '=')
				return (1);
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

void	apply_case(int case_type, char *arg, int *status, t_env **env)
{
	if (case_type == -1)
	{
		(ft_print_err("minishell: export: `"), ft_print_err(arg));
		ft_print_err("': not a valid identifier\n");
		*status = 1;
	}
	else if (case_type == 0)
		zero_case(env, arg);
	else if (case_type == 1)
		one_case(env, arg);
	else if (case_type == 2)
		two_case(env, arg);
}

int	ft_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env->next)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_export(char **args, t_env **env)
{
	int	i;
	int	case_type;
	int	status;

	status = 0;
	if (!args[1])
		status = print_env(env);
	else
	{
		i = 1;
		while (args[i])
		{
			case_type = valid_case(args[i]);
			apply_case(case_type, args[i], &status, env);
			i++;
		}
	}
	return (status);
}
