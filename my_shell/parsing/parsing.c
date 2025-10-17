/* ************************************************************************** */
/*			*/
/*		:::	  ::::::::   */
/*   parsing.c		  :+:	  :+:	:+:   */
/*			+:+ +:+		 +:+	 */
/*   By: sabadri <sabadri@student.42.fr>			+#+  +:+	   +#+		*/
/*		+#+#+#+#+#+   +#+		   */
/*   Created: 2025/04/25 03:53:18 by sabadri		   #+#	#+#			 */
/*   Updated: 2025/05/26 16:42:14 by sabadri		  ###   ########.fr	   */
/*			*/
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_line **ll)
{
	t_line	*tmp;
	t_line	*next;

	tmp = *ll;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->line)
			free(tmp->line);
		free(tmp);
		tmp = next;
	}
	*ll = NULL;
}

static t_line	*create_line(char *str, int *index, t_garbage **gcol)
{
	t_line	*new_line;
	char	*tmp;

	new_line = ft_malloc(sizeof(t_line), gcol);
	if (!new_line)
		return (NULL);
	tmp = select_content(str, index, gcol);
	new_line->line = ft_strdup_g(tmp, gcol);
	new_line->token.tok = select_token(new_line->line);
	new_line->token.quotes = 0;
	new_line->token.imbigious = 0;
	new_line->next = NULL;
	return (new_line);
}

static t_line	*process_str(t_line **ll, char *str, t_garbage **gcol)
{
	t_line	*current;
	int		i;
	t_line	*new_line;

	i = 0;
	current = *ll;
	while (str[i] != '\0')
	{
		new_line = create_line(str, &i, gcol);
		if (!new_line)
			return (NULL);
		if (*ll == NULL)
		{
			*ll = new_line;
			current = new_line;
		}
		else
		{
			current->next = new_line;
			current = new_line;
		}
	}
	return (*ll);
}

t_line	*llc(t_line **ll, char *str, t_garbage **gcol)
{
	if (!str)
		return (NULL);
	return (process_str(ll, str, gcol));
}

t_args	*parsing(char *str, t_env **tenv, t_garbage **gcol)
{
	t_args	*args_ll;
	t_line	*ll;

	ll = NULL;
	if (!syntax_check(str))
		return (env_update_value("?", ft_strdup("2"), tenv), NULL);
	ll = llc(&ll, str, gcol);
	if (!ll)
		return (ft_free(&ll), NULL);
	ll = s_or_d_or_v(&ll, gcol);
	if (!second_llc(&ll, tenv))
	{
		ft_print_err("minishell: syntax error near unexpected token\n");
		env_update_value("?", ft_strdup("2"), tenv);
		return (NULL);
	}
	ll = expanding(&ll, tenv, gcol);
	ll = split_var(&ll, gcol);
	ll = remove_emptyexp(&ll, gcol);
	ll = remove_redirections(&ll, gcol);
	ll = final_joining(&ll, gcol);
	args_ll = ll_to_args(&ll, gcol);
	return (args_ll);
}
