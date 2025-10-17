/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:51:49 by monabati          #+#    #+#             */
/*   Updated: 2025/06/23 11:02:26 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include "libft_garb_collect/libft.h"

// Text colors/style
# define RED     "\001\x1b[31m\002"
# define GREEN   "\001\x1b[32m\002"
# define YELLOW  "\001\x1b[33m\002"
# define BLUE    "\001\x1b[34m\002"
# define BRIGHT_CYAN    "\001\x1b[96m\002"
# define BOLD      "\001\x1b[1m\002"
# define RESET     "\001\x1b[0m\002"

//macros norm
# define SECURE_PATH "PATH=/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin"
# define CD_ERROR "cd: error retrieving current directory:\
 getcwd: cannot access parent directories"

//global variable for signals
extern int	g_sig;

typedef enum e_token_type
{
	UNKNOWN,
	t_SPACE,
	PIPE,
	COMMAND,
	HERE_DOC,
	IN_REDIRECT,
	OUT_REDIRECT,
	INFILE,
	OUTFILE,
	DELIMITER,
	APPEND,
	TOBEAPPENDED,
	SQUOTES,
	DQUOTES,
	VAR,
	EXPANDED,
	EMPTY_EXP,
	CHECK,
	IMBIG
}	t_token_type;

typedef struct s_files
{
	char			*name;
	int				type;
	int				imbigious;
	struct s_files	*next;
}	t_files;

typedef struct s_args
{
	char			**args;
	t_files			*files;
	int				fd_out;
	int				fd_in;
	int				tmp_heredoc;
	int				need_to_exit;
	struct s_args	*next;
}	t_args;

typedef struct s_tok
{
	int	tok;
	int	quotes;
	int	imbigious;
}	t_tok;

typedef struct s_list
{
	char			*line;
	t_tok			token;
	struct s_list	*next;
}	t_line;

//env struct
typedef struct s_env
{
	char			*name;
	char			*value;
	bool			env_visibilty;
	bool			can_be_deleted;
	struct s_env	*next;
}	t_env;

// for herdoc
typedef struct s_herdoc
{
	int	type;
	int	write_fd;
	int	read_fd;
}	t_herdoc;

typedef struct s_pipes
{
	int	**pipes;
	int	std[2];
}	t_pipes;

typedef struct s_env_garb
{
	t_env		**env;
	t_garbage	**garb_coll;
}	t_env_garb;

typedef struct s_expand_ctx
{
	t_env		**env;
	t_garbage	**gcol;
}	t_exp;

//set_env
t_env		*ft_creat_env_list(char **tenv);
t_env		*last_node(t_env *env);
void		node_add_back(t_env **env, t_env *node);
t_env		*creat_node(t_env **env, char *str, int stat, int can_be_deleted);
int			is_path_exist(t_env **env);
void		if_env_exist(char **tenv, t_env **env);
void		if_env_not_exist(t_env **env);
void		ft_del_node(t_env *node);
void		ft_clear_list(t_env **env);
char		**sub_env(char *env);
char		*sub_name(char *str, size_t *cut);

//env serch for value && update value
int			env_update_value(char *name, char *value, t_env **env);
char		*env_search_value(char *name, t_env **env);
char		*env_search_value_g(char *name, t_env **env, t_garbage **garb_coll);

//built-in
int			ft_cd(char **args, t_env **env);
int			ft_cd1(t_env **env);
int			ft_cd2(char **args, t_env **env);
void		update_pwd(t_env **env);
void		update_pwd_in_err(t_env **env, char *path);
void		update_old_pwd(t_env **env, char *old_pwd);
int			ft_echo(char **args, t_env **env);
int			ft_env(t_env **env);
int			ft_exit(char **args, int *std, t_env **env, t_garbage **garb_coll);
int			ft_export(char **args, t_env **env);
int			print_env(t_env **env);
void		apply_case(int case_type, char *arg, int *status, t_env **env);
int			valid_case(char *str);
void		zero_case(t_env **env, char *arg);
void		one_case(t_env **env, char *arg);
int			two_case2(t_env **env, char **all);
void		two_case(t_env **env, char *arg);
void		free_double(char **str);
int			ft_list_size(t_env *env);
int			ft_pwd(char **args, t_env **env);
int			ft_unset(char **args, t_env **env);
int			exec_built_in(char **args, int *std,
				t_env **env, t_garbage **garb_coll);

//parsing
t_args		*parsing(char *str, t_env **env, t_garbage **gcollect);
t_args		*ll_to_args(t_line **ll, t_garbage **gcol);
int			is_valid_var_name(char c);
char		*select_content(char *str, int *i, t_garbage **gcol);
int			second_llc(t_line **ll, t_env **tenv);
t_line		*s_or_d_or_v(t_line **ll, t_garbage **gcole);
int			select_token(char *s);
bool		syntax_check(const char *str);
int			redirection_or_heredoce(char *s);
char		*handle_2quotes(char *str, int *i, t_garbage **gcol);
char		*handle_squote(char *str, int *i, t_garbage **gcol);
char		*handle_pipe(int *i, t_garbage **gcol);
t_line		*remove_emptyexp(t_line **head, t_garbage **gcol);
t_line		*remove_redirections(t_line **ll, t_garbage **gcol);
void		list_add_files(t_files **list, t_line *temp, int tp, t_garbage **g);
t_line		*expanding(t_line **ll, t_env **env, t_garbage **gcol);
t_line		*split_var(t_line **ll, t_garbage **gcol);
int			count_word(const char *str);
int			dsign_check(char *str);
t_line		*handle_pipe_token(t_line *current, int *syn_error);
char		*handle_pipe(int *i, t_garbage **gcol);
char		*ft_strndup(const char *s, size_t n, t_garbage **g);
int			is_valid_var_start(char c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strcpy(char *dest, const char *src);
char		*expand_var(char *input, t_env **envp, t_garbage **gcol);
t_line		*final_joining(t_line **ll, t_garbage **gcol);
void		append_line_node(t_line **head, t_line *new_node);
t_line		*new_line_node(char *line, int tok, t_garbage **gcol);
void		handle_var_and_quotes(t_line *current, t_env **tenv, t_garbage **g);
void		handle_file_tokens(t_line *c, t_env **tenv, t_garbage **g);
char		*expand_all(char *str, t_env **env, t_garbage **gcol);

//execution
void		execution(t_args **parsing, t_env **env, t_garbage **garb_coll);
void		open_file(t_args **parcing, t_env **env, t_garbage **garb_coll);
void		open_files1(t_args *tmp, t_files *files, int *fd_in, int *fd_out);
int			here_doc(char *delimiter, int type,
				t_env **env, t_garbage **garb_coll);
void		write_herdoc_expand(char *str, int write_tmp,
				t_env **env, t_garbage **garb_coll);
char		**switch_list_to_double(t_env **env_list, t_garbage **garb_coll);
char		*get_cmd_path(char *cmd, t_env **env, t_garbage **garb_coll);
int			check_cmd(char *cmd, char *cmd_path,
				t_env **env, t_garbage **garb_coll);
int			does_has_slash(char *str);
int			execution_one(t_args **parsing, t_env **env,
				t_garbage **garb_coll, int *fd);
int			multi_cmd(t_args **parcing, int *tmp,
				t_env **env, t_garbage **garb_coll);

int			parsing_size(t_args *list);
int			**creat_pipe(int num, t_garbage **garb_coll);

void		close_pipes(int **pipes);
void		close_pipe_first_child(int **pipes);
void		middle_pipe_close(int **pipes, int num);
int			close_pipe_last_child(int **pipes);

void		first_child(t_args **parcing, t_pipes pipes,
				t_env **env, t_garbage **garb_coll);
void		free_middle_child(t_pipes pipes, int cmd_count,
				t_env **env, t_garbage **garb_coll);
void		in_middle_childs(t_args **parcing, t_pipes pipes,
				t_env **env, t_garbage **garb_coll);
void		in_middle_childs1(t_args *tmp, t_pipes pipes,
				int cmd_count, t_env_garb middle);
int			last_child(t_args **parcing, t_pipes pipes,
				t_env **env, t_garbage **garb_coll);
t_args		*last_cmd(t_args **cmds);
int			get_exit_status(int status);
void		minishell_sigint(int signum);
void		signals_init(void);
void		signals_reset(void);
void		check_herdoc_signal(int status);
void		change_signal(t_env **env);

#endif
