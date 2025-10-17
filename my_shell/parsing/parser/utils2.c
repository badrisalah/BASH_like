/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:47:15 by sabadri           #+#    #+#             */
/*   Updated: 2025/05/30 01:47:18 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	check_quotes(const char *str, int *i, char quote)
{
	int	count;

	count = 1;
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == quote)
		{
			count++;
			break ;
		}
		(*i)++;
	}
	return (count);
}

bool	syntax_check(const char *str)
{
	int	i;
	int	count;

	if (!str)
		return (false);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count = check_quotes(str, &i, '\'');
		else if (str[i] == '"')
			count = check_quotes(str, &i, '"');
		if (count != 0 && count != 2)
			break ;
		i++;
	}
	if (count != 0 && count != 2)
		ft_print_err("syntax error : missing operator '\'' or '\"' \n");
	return (count == 2 || count == 0);
}
