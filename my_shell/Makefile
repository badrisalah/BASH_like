SRCS	=	built_in/exec_built_in.c \
			built_in/ft_cd.c \
			built_in/ft_cd_utils.c \
			built_in/ft_echo.c \
			built_in/ft_env.c \
			built_in/ft_exit.c \
			built_in/ft_export.c \
			built_in/ft_export_utils.c \
			built_in/ft_export_utils2.c \
			built_in/ft_pwd.c \
			built_in/ft_unset.c \
			env_update_search/env_update_search.c \
			execution/exec_cmds.c \
			execution/multi_cmd/close_pipes_childs.c \
			execution/multi_cmd/creat_pipes.c \
			execution/multi_cmd/first_child.c \
			execution/multi_cmd/last_child.c \
			execution/multi_cmd/middle_childs.c \
			execution/multi_cmd/multi_cmd.c \
			execution/multi_cmd/utils.c \
			execution/one_cmd/one_cmd.c \
			execution/open_files/herdoc_utils.c \
			execution/open_files/heredoc.c \
			execution/open_files/open_files.c \
			execution/open_files/open_files1.c \
			execution/utils/check_file.c \
			execution/utils/check_file1.c \
			execution/utils/child_exit_status.c \
			execution/utils/cmd_path.c \
			execution/utils/list_to_double.c \
			libft_garb_collect/ft_atoi.c \
			libft_garb_collect/ft_atoll.c \
			libft_garb_collect/ft_bzero.c \
			libft_garb_collect/ft_calloc.c \
			libft_garb_collect/ft_isalnum.c \
			libft_garb_collect/ft_isalpha.c \
			libft_garb_collect/ft_isascii.c \
			libft_garb_collect/ft_isdigit.c \
			libft_garb_collect/ft_isprint.c \
			libft_garb_collect/ft_isspace.c \
			libft_garb_collect/ft_itoa.c \
			libft_garb_collect/ft_itoa_g.c \
			libft_garb_collect/ft_memchr.c \
			libft_garb_collect/ft_memcmp.c \
			libft_garb_collect/ft_memcpy.c \
			libft_garb_collect/ft_memmove.c \
			libft_garb_collect/ft_memset.c \
			libft_garb_collect/ft_print_err.c \
			libft_garb_collect/ft_putchar_fd.c \
			libft_garb_collect/ft_putendl_fd.c \
			libft_garb_collect/ft_putnbr_fd.c \
			libft_garb_collect/ft_putstr_fd.c \
			libft_garb_collect/ft_split.c \
			libft_garb_collect/ft_split_g.c \
			libft_garb_collect/ft_strchr.c \
			libft_garb_collect/ft_strcmp.c \
			libft_garb_collect/ft_strdup.c \
			libft_garb_collect/ft_strdup_g.c \
			libft_garb_collect/ft_striteri.c \
			libft_garb_collect/ft_strjoin.c \
			libft_garb_collect/ft_strjoin_g.c \
			libft_garb_collect/ft_strlcat.c \
			libft_garb_collect/ft_strlcpy.c \
			libft_garb_collect/ft_strlen.c \
			libft_garb_collect/ft_strncmp.c \
			libft_garb_collect/ft_strnstr.c \
			libft_garb_collect/ft_strrchr.c \
			libft_garb_collect/ft_strtrim.c \
			libft_garb_collect/ft_strtrim_g.c \
			libft_garb_collect/ft_substr.c \
			libft_garb_collect/ft_substr_g.c \
			libft_garb_collect/ft_tolower.c \
			libft_garb_collect/ft_toupper.c \
			libft_garb_collect/garb_coll_clear.c \
			libft_garb_collect/garb_coll_init.c \
			parsing/expander/expand_utils.c \
			parsing/expander/expanding.c \
			parsing/expander/expanding_utils2.c \
			parsing/expander/expanding_utils3.c \
			parsing/ll_helper/args_from_ll.c \
			parsing/ll_helper/args_from_ll2.c \
			parsing/parser/joining.c \
			parsing/parser/joining_utils.c \
			parsing/parser/pipe_handle.c \
			parsing/parser/select_content.c \
			parsing/parser/utils.c \
			parsing/parser/utils2.c \
			parsing/parser/utils3.c \
			parsing/parser/utils4.c \
			parsing/parsing.c \
			set_env/env_creat_utils.c \
			set_env/env_creat_utils2.c \
			set_env/env_free_utils.c \
			set_env/sub_env.c \
			signals/signals.c \
			main.c
OBJS	= ${SRCS:.c=.o}
NAME	= minishell
CC		= cc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -lreadline -o ${NAME} #-fsanitize=address -g

%.o: %.c libft_garb_collect/libft.h minishell.h
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all
