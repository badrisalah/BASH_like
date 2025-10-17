/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:46:49 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/16 14:49:22 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_dsign(char *str, int *i, t_garbage **gcol)
{
	int	j;

	j = *i;
	while (str[*i] == '$')
		(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_substr_g(str, j, *i - j, gcol));
	}
	if (str[*i] && is_valid_var_start(str[*i]))
	{
		while (str[*i] && is_valid_var_name(str[*i]))
			(*i)++;
	}
	return (ft_substr_g(str, j, *i - j, gcol));
}

static char	*handle_spaces(char *str, int *i, t_garbage **gcol)
{
	while (str[*i] == ' ' || str[*i] == '\t')
		(*i)++;
	return (ft_strdup_g(" ", gcol));
}

static char	*handle_redirections(char *str, int *i, t_garbage **gcol)
{
	int		start;
	int		count;
	char	c;

	count = 0;
	start = *i;
	c = str[*i];
	while (str[*i] == c && count < 2)
	{
		(*i)++;
		count++;
	}
	return (ft_substr_g(str, start, *i - start, gcol));
}

static char	*handle_normal_text(char *str, int *i, t_garbage **gcol)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '"' && str[*i] != '|' && str[*i] != '<'
		&&str[*i] != '>' && str[*i] != ' '
		&& str[*i] != '\t' && str[*i] != '\'' && str[*i] != '$')
	{
		(*i)++;
	}
	return (ft_substr_g(str, start, *i - start, gcol));
}

char	*select_content(char *str, int *i, t_garbage **gcol)
{
	if (str[*i] == ' ' || str[*i] == '\t')
		return (handle_spaces(str, i, gcol));
	if (str[*i] == '<' || str[*i] == '>')
		return (handle_redirections(str, i, gcol));
	if (str[*i] == '"')
		return (handle_2quotes(str, i, gcol));
	if (str[*i] == '\'')
		return (handle_squote(str, i, gcol));
	if (str[*i] == '|')
		return (handle_pipe(i, gcol));
	if (str[*i] == '$')
		return (handle_dsign(str, i, gcol));
	return (handle_normal_text(str, i, gcol));
}
