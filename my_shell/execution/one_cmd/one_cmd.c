/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 15:20:28 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:54 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	redirection1(t_args *tmp, int *status)
{
	if (tmp->fd_in != -2 && tmp->fd_out == -2)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(tmp->fd_in);
	}
	else if (tmp->fd_in == -2 && tmp->fd_out != -2)
	{
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), *status = 1);
		close(tmp->fd_out);
	}
}

static int	redirection(t_args **parsing)
{
	t_args	*tmp;
	int		status;

	tmp = *parsing;
	status = 0;
	if (tmp->fd_in == -2 && tmp->fd_out == -2)
	{
		return (0);
	}
	else if (tmp->fd_in != -2 && tmp->fd_out != -2)
	{
		if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
			(perror("dup2"), status = 1);
		if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
			(perror("dup2"), status = 1);
		close(tmp->fd_in);
		close(tmp->fd_out);
	}
	else
		redirection1(tmp, &status);
	return (status);
}

static void	child(t_args **parsing, t_env **env, t_garbage **garb_coll)
{
	t_args	*tmp;
	char	*cmd_path;
	char	**envp;
	int		check;

	tmp = *parsing;
	cmd_path = get_cmd_path(tmp->args[0], env, garb_coll);
	envp = switch_list_to_double(env, garb_coll);
	check = check_cmd(tmp->args[0], cmd_path, env, garb_coll);
	if (check != 0)
		exit(check);
	if (execve(cmd_path, tmp->args, envp) == -1)
		perror(tmp->args[0]);
	ft_clear_list(env);
	garbage_clear(garb_coll);
	exit (127);
}

int	exec_cmd(t_args **parsing, t_env **env, t_garbage **garb_coll, int *fd)
{
	int	id;
	int	status;

	g_sig = 1;
	id = fork();
	if (id == -1)
		perror("fork");
	if (id == 0)
	{
		signals_reset();
		(close(fd[0]), close(fd[1]));
		if ((*parsing)->need_to_exit == 1)
			exit(2);
		if (!(*parsing)->args[0])
			exit(0);
		child(parsing, env, garb_coll);
	}
	waitpid(id, &status, 0);
	return (get_exit_status(status));
}

int	execution_one(t_args **parsing, t_env **env, t_garbage **garb_coll, int *fd)
{
	t_args	*tmp;
	int		status;

	tmp = *parsing;
	if (!tmp->args || !tmp->args[0])
	{
		if (tmp->need_to_exit == 1)
			return (1);
		return (0);
	}
	if (tmp->need_to_exit == 1)
		return (1);
	status = redirection(parsing);
	if (status == 1)
		return (status);
	status = exec_built_in(tmp->args, fd, env, garb_coll);
	if (status == -1)
	{
		status = exec_cmd(parsing, env, garb_coll, fd);
	}
	return (status);
}
