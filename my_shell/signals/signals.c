/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:50:14 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:17 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	minishell_sigint(int signum)
{
	(void)signum;
	if (g_sig == 1 || g_sig == 130)
		return ;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
	change_signal(NULL);
}

void	signals_init(void)
{
	signal(SIGINT, minishell_sigint);
	signal(SIGQUIT, SIG_IGN);
	g_sig = 0;
}

void	signals_reset(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	check_herdoc_signal(int status)
{
	if (WIFSIGNALED(status))
	{
		g_sig = 130;
		write(1, "\n", 1);
	}
}
