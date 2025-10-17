/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:50:29 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:08 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **args, t_env **env)
{
	char	*pwd;

	(void)args;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		pwd = env_search_value("PWD", env);
	}
	write(1, pwd, ft_strlen(pwd));
	write (1, "\n", 1);
	free(pwd);
	return (0);
}
