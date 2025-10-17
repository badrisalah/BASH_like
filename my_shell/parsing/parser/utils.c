/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:47:10 by sabadri           #+#    #+#             */
/*   Updated: 2025/05/30 01:52:23 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_squote(char *str, int *i, t_garbage **gcol)
{
	int	j;

	j = *i;
	(*i)++;
	while (str[*i] != '\'' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr_g(str, j, *i - j, gcol));
}

char	*handle_2quotes(char *str, int *i, t_garbage **gcol)
{
	int	j;

	j = *i;
	(*i)++;
	while (str[*i] != '"' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '"')
		(*i)++;
	return (ft_substr_g(str, j, *i - j, gcol));
}

int	redirection_or_heredoce(char *s)
{
	if (!ft_strcmp(s, "<<"))
		return (4);
	else if (!ft_strcmp(s, "<"))
		return (5);
	else if (!ft_strcmp(s, ">"))
		return (6);
	else if (!ft_strcmp(s, ">>"))
		return (10);
	return (0);
}

int	s_or_d_quotes(char *str)
{
	if (*str == '\'')
		return (12);
	else if (*str == '"')
		return (13);
	return (14);
}

int	select_token(char *s)
{
	int	k;

	k = 1e9;
	if (*s == ' ')
		return (1);
	else if (*s == '|')
		return (2);
	else if (!redirection_or_heredoce(s))
		return (3);
	else
		k = redirection_or_heredoce(s);
	return (k);
}
