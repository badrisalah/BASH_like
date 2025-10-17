/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:48:39 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:01:02 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	herdoc_break(char *delimiter, char *str)
{
	if (!str)
	{
		ft_print_err("minishell: warning: ");
		ft_print_err("here-document delimited by end-of-file (wanted `");
		ft_print_err(delimiter);
		ft_print_err("')\n");
		return (1);
	}
	if (ft_strcmp(delimiter, str) == 0)
	{
		free(str);
		return (1);
	}
	return (0);
}

static void	heredoc_2(char *delimiter, t_herdoc herdoc,
	t_env **env, t_garbage **garb_coll)
{
	char	*str;

	close(herdoc.read_fd);
	while (1)
	{
		str = readline("> ");
		if (herdoc_break(delimiter, str) == 1)
			break ;
		if (herdoc.type == DELIMITER)
			write_herdoc_expand(str, herdoc.write_fd, env, garb_coll);
		else if (herdoc.type == 1e9)
		{
			write(herdoc.write_fd, str, ft_strlen(str));
			write(herdoc.write_fd, "\n", 1);
		}
		free(str);
	}
	close(herdoc.write_fd);
	rl_clear_history();
	exit(0);
}

int	here_doc(char *delimiter, int type,
	t_env **env, t_garbage **garb_coll)
{
	t_herdoc	herdoc;
	int			id;
	int			status;

	unlink("/tmp/.her\tdoc\n");
	herdoc.write_fd = open("/tmp/.her\tdoc\n",
			O_CREAT | O_TRUNC | O_WRONLY, 0666);
	herdoc.read_fd = open("/tmp/.her\tdoc\n", O_RDONLY);
	if (herdoc.write_fd == -1 || herdoc.read_fd == -1)
	{
		(1) && (close(herdoc.write_fd), close(herdoc.read_fd));
		return (ft_print_err("minishell: here-document: Permission denied\n"),
			-1);
	}
	unlink("/tmp/.her\tdoc\n");
	(1) && (g_sig = 1, id = fork());
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		herdoc.type = type;
		heredoc_2(delimiter, herdoc, env, garb_coll);
	}
	waitpid(id, &status, 0);
	check_herdoc_signal(status);
	return (close(herdoc.write_fd), herdoc.read_fd);
}
