/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:38:41 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 10:59:39 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_old_pwd(t_env **env, char *old_pwd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(old_pwd);
			return ;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(t_env **env)
{
	t_env	*tmp;
	char	*cwd;

	tmp = *env;
	cwd = getcwd(NULL, 0);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			update_old_pwd(env, tmp->value);
			free(tmp->value);
			tmp->value = cwd;
			return ;
		}
		tmp = tmp->next;
	}
	free(cwd);
}

void	update_pwd_in_err(t_env **env, char *path)
{
	t_env	*tmp;
	char	*tnew_path;
	char	*new_path;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			tnew_path = ft_strjoin(tmp->value, "/");
			new_path = ft_strjoin(tnew_path, path);
			free(tnew_path);
			update_old_pwd(env, tmp->value);
			free(tmp->value);
			tmp->value = new_path;
			break ;
		}
		tmp = tmp->next;
	}
}
