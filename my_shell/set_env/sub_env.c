/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:16 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:13 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sub_name(char *str, size_t *cut)
{
	size_t	len;
	size_t	i;
	char	*name;

	len = 0;
	i = 0;
	while (str[len] != '=' && str[len])
		len++;
	name = malloc(sizeof(char) * (len + 1));
	if (!name)
	{
		perror("malloc");
		exit(1);
	}
	while (i < len)
	{
		name[i] = str[i];
		i++;
	}
	name[i] = '\0';
	if (str[len] == '=')
		len++;
	*cut = len;
	return (name);
}

char	**sub_env(char *env)
{
	char	**all;
	size_t	cut;

	all = malloc(sizeof(char *) * 3);
	if (!all)
	{
		perror("malloc");
		exit(1);
	}
	all[0] = sub_name(env, &cut);
	all[1] = ft_strdup(env + cut);
	all[2] = NULL;
	return (all);
}
