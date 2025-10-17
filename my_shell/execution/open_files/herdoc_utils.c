/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:20:09 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:59 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*convert_to_str(char c, t_garbage **garb_coll)
{
	char	*str;

	str = ft_malloc(sizeof(char) * 2, garb_coll);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*expand_var_herdoc(char *str, int *i,
	t_env **env, t_garbage **garb_coll)
{
	char	*tmp;
	int		j;

	(1) && (tmp = ft_strdup_g("", garb_coll), j = 0);
	while (str[j] == '$')
		j++;
	if (j % 2 == 0)
	{
		*i = *i + j;
		return (ft_strdup_g("", garb_coll));
	}
	if (str[j] == '?')
	{
		tmp = ft_strjoin_g(tmp, convert_to_str(str[j], garb_coll), garb_coll);
		j++;
	}
	while (ft_isalnum(str[j]))
	{
		tmp = ft_strjoin_g(tmp, convert_to_str(str[j], garb_coll), garb_coll);
		j++;
	}
	*i = *i + j;
	return (env_search_value_g(tmp, env, garb_coll));
}

char	*expande_heredoc(char *str, t_env **env, t_garbage **garb_coll)
{
	char	*expand;
	int		i;

	i = 0;
	expand = ft_strdup_g("", garb_coll);
	while (str[i])
	{
		if (str[i] == '$')
		{
			expand = ft_strjoin_g(expand,
					expand_var_herdoc(&str[i], &i, env, garb_coll), garb_coll);
			continue ;
		}
		expand = ft_strjoin_g(expand, convert_to_str(str[i], garb_coll),
				garb_coll);
		i++;
	}
	return (expand);
}

void	write_herdoc_expand(char *str, int write_tmp,
	t_env **env, t_garbage **garb_coll)
{
	char	*tmp;

	tmp = expande_heredoc(str, env, garb_coll);
	write(write_tmp, tmp, ft_strlen(tmp));
	write(write_tmp, "\n", 1);
}
