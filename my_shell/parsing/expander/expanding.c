/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:12:30 by sabadri           #+#    #+#             */
/*   Updated: 2025/06/18 14:53:46 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_and_expand(char *str, int *i, t_env **env, t_garbage **g)
{
	int		j;
	char	*expanded;
	char	*expand;
	char	*result;

	j = 0;
	while (ft_isalpha(str[*i]) || str[*i] == '_' || str[*i] == '?')
	{
		j++;
		(*i)++;
	}
	if (j == 0)
		return (ft_strdup(""));
	expanded = ft_substr_g(str, *i - j, j, g);
	expand = env_search_value_g(expanded, env, g);
	if (!expand)
		result = ft_strdup_g("", g);
	else
		result = ft_strdup_g(expand, g);
	return (result);
}

static void	append_non_dollar_char(char **final, char *str, int *i, t_exp *c)
{
	char	*tmp;

	tmp = ft_substr_g(str, *i, 1, c->gcol);
	*final = ft_strjoin_g(*final, tmp, c->gcol);
	(*i)++;
}

static void	handle_dollar_sequence(char **final, char *str, int *i, t_exp *c)
{
	char	*tmp;

	(*i)++;
	if (str[*i] == '_' || is_valid_var_start(str[*i]) || str[*i] == '?')
		tmp = extract_and_expand(str, i, c->env, c->gcol);
	else
		tmp = ft_strdup_g("$", c->gcol);
	*final = ft_strjoin_g(*final, tmp, c->gcol);
}

char	*expand_all(char *str, t_env **env, t_garbage **gcol)
{
	char			*final;
	int				i;
	t_exp			ctx;

	if (!str)
		return (NULL);
	ctx.env = env;
	ctx.gcol = gcol;
	final = ft_strdup_g("", gcol);
	i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			append_non_dollar_char(&final, str, &i, &ctx);
		else
			handle_dollar_sequence(&final, str, &i, &ctx);
	}
	return (final);
}

t_line	*expanding(t_line **ll, t_env **tenv, t_garbage **g)
{
	t_line	*current;

	current = *ll;
	while (current)
	{
		handle_var_and_quotes(current, tenv, g);
		handle_file_tokens(current, tenv, g);
		current = current->next;
	}
	return (*ll);
}
