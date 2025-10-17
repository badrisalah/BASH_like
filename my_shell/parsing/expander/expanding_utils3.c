/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:40:44 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/18 14:48:06 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_var_and_quotes(t_line *current, t_env **tenv, t_garbage **g)
{
	if (current->token.tok == VAR)
	{
		current->line = expand_var(current->line, tenv, g);
		current->token.tok = EXPANDED;
	}
	else if (current->token.tok == DQUOTES && dsign_check(current->line))
	{
		current->line = expand_all(current->line, tenv, g);
	}
}

void	handle_file_tokens(t_line *c, t_env **tenv, t_garbage **g)
{
	if ((c->token.tok == INFILE || c->token.tok == OUTFILE
			|| c->token.tok == TOBEAPPENDED) && dsign_check(c->line))
	{
		if (c->token.quotes == 0)
		{
			c->line = ft_strdup_g(expand_all(c->line, tenv, g), g);
			c->token.imbigious = 1;
		}
		else if (c->token.quotes == 1e9 - 1)
		{
			c->line = ft_strdup_g(expand_all(c->line, tenv, g), g);
			c->token.tok = OUTFILE;
		}
	}
}

int	count_word(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r')
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

int	dsign_check(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}

char	*expand_var(char *input, t_env **envp, t_garbage **gcol)
{
	char	*result;
	int		count;
	size_t	i;

	i = 0;
	count = 0;
	while (input[i] == '$')
	{
		count++;
		i++;
	}
	input += i;
	if (ft_strlen(input - 1) == 1 || (i == ft_strlen(input - 1)))
		return ("$");
	else if (count % 2 == 0)
		return (input);
	result = env_search_value_g(input, envp, gcol);
	if (!result)
		return (ft_strdup_g("", gcol));
	return (result);
}
