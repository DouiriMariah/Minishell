/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:55:04 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:24:21 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define B_ERR_ENV1	"env: invalid option -- '"
# define A_ERR_ENV1	"'\nTry 'env --help' for more information.\n"
# define B_ERR_ENV2	"env: '"
# define A_ERR_ENV2	"’: No such file or directory\n"
# define B_ERR_EXIT	"bash: exit: "
# define A_ERR_EXIT	": numeric argument required\n"
# define B_ERR_EXPORT "bash: export: -"
# define A_ERR_EXPORT	": invalid option\n"
# define B_ERR_PWD	"bash: pwd: -"
# define A_ERR_PWD	": invalid option\npwd: usage: pwd [-LP]\n"
# define B_ERR_CMD	"bash: "
# define A_ERR_CMD1	": command not found\n"
# define A_ERR_CMD2  ": No such file or directory\n"
# define ERR_CHEV_PIPE1 "bash: syntax error near unexpected token `|'\n"
# define ERR_CHEV_PIPE2 "bash: syntax error near unexpected token `||'\n"
# define ERR_CHEV_NEWLINE "bash: syntax error near unexpected token `newline'\n"
# define ERR_HD_EOF	"bash: warning: here-document delimited by end-of-file \n"
# define ENV_I	"PWD=/mnt/nfs/homes/amattei/Merge_Minishell/Mini_ange"

typedef enum e_token_type
{
	BUILTIN,
	ENTRY,
	EXIT,
	LIMIT,
	EXIT_APPEND,
	WORD_N,
	WORD,
	FILE_IN,
	FILEOUT,
	FILE_APPEND,
	HEREDOC,
}	t_token_type;

typedef struct s_tokenisation
{
	char					*separated;
	int						position;
	t_token_type			type;
	struct s_tokenisation	*next;
	struct s_tokenisation	*prev;
}	t_tokenisation;

typedef struct s_exec
{
	t_tokenisation	*head_process;
	char			**wordi;
	int				pos_process;
	int				file1;
	int				file2;
	int				builtin;
	struct s_exec	*next;
}	t_exec;

typedef struct s_ecosystem
{
	int					i;
	char				*tree;
	char				*leaf;
	struct s_ecosystem	*next;
}	t_ecosystem;

typedef struct s_mini
{
	pid_t			fork;
	int				dol;
	int				nb_process;
	int				old_str;
	int				new_str;
	int				nb_heredoc;
	int				v;
	int				i;
	int				j;
	int				env_length;
	int				stock_hdoc;
	int				builtin;
	int				pipe_fd[2];
	int				after;
	int				good_stdout;
	int				before;
	int				status;
	char			**heredoc_tab;
	char			**envp;
	char			*newi;
	char			*final_str;
	char			**process;
	t_tokenisation	*head_token;
	t_tokenisation	*tokens;
	t_ecosystem		*head;
	t_ecosystem		*envir;
	t_exec			*all;
	t_exec			*head_all;
}	t_mini;

char			*get_env(char *str, t_mini *shell);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_check_pipe(char *str, t_mini *shell);
char			*ft_strdup(char *src);
char			*ft_strdup_split( char *src, int start, int end);
char			**ft_split(char *s, char c);
char			**ft_split_dans_process(char *s, char c);
char			*ft_itoa(int n);
char			*ft_strdupo(char *s, int i);
char			*get_next_line(int fd);
char			*ft_strjoini(char *s1, char *s2, t_mini *shell);

int				ft_strlen(char *str);
int				twin_char(char *s1, char *s2);
int				quote(char *str, int *i);
int				final_string(char *str, t_mini *shell);
int				give_me_the_money2(char *str, t_mini *shell, int who);
int				total_len_dans_process(char *s, char c);
int				ft_atoi(const char *nptr);
int				ft_doublons(char *str, char c);
int				pipo(char c);
int				chevron(char c);
int				ft_separateur(char c);
int				not_alphanumeric(char c);
int				ft_double_chev(char *str, int max);
int				option_n(char *str);
int				check_str(char *str);
int				have_you_hd(t_mini *shell);
int				are_you_finished(t_mini *shell, char *str);
int				ft_found_char(char *str, char c);
int				ft_str(char *env, char *find);
int				ft_strcmp(char *s1, char *s2);
int				sep(char c);
int				open_files(t_mini *shell, int type, char *sep);

void			free_exit(t_mini *shell);
void			error_message(char *b_w, char *wordi, char *a_w, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_builtin(t_mini *shell);
void			ft_pwd(t_mini *shell);
void			ft_echo(t_mini *shell);
void			ft_cd(t_mini *shell);
void			ft_export(char **str, t_mini *shell);
void			ft_unset(char **str, t_mini *shell);
void			ft_print_env(t_mini*shell);
void			ft_env(t_mini *shell);
void			init_data(char **env, t_mini*shell);
void			ft_continu2(char *str, t_mini *shell, int who);
void			ft_continu(char *str, t_mini *shell, int tmp);
void			fill_new_str(t_mini *shell, char *str);
void			ft_exit(t_mini *shell);
void			ft_lst_add_back(t_mini *shell, t_ecosystem *new);
void			ft_routine(t_mini *shell, int i);
void			ft_cut_env(t_mini *shell);
void			fill_tokens(t_mini *shell, int j);
void			ft_free_node(t_mini *shell, char *name);
void			ft_exec(t_mini *shell);
void			ft_one_unset(char *str, t_mini *shell);
void			update_env(t_mini *shell);
void			ft_export_bis(t_mini *shell, char *str);
void			ft_free_test(t_mini *shell);
void			free_double_char(char **str);
void			ft_free_env(t_ecosystem *start, t_mini *shell);
void			ft_last(t_mini *shell);
void			run_signals(int sig);
void			copy_env(t_mini *shell, char **env);
void			ft_close(t_mini *shell);
void			close_child(t_mini *shell);
void			fork_with_hd(t_mini *shell);
void			ft_heredoc(t_mini *shell);
void			dup_files(t_mini *shell);
void			close_child_alone(t_mini *shell);
void			child_hd(t_mini *shell);
void			money_2_help(t_mini *shell, char *tmp);
void			fill_tmp_gm2(t_mini *shell, char *str, int who, char *tmp);
void			ft_continu(char *str, t_mini *shell, int tmp);
void			if_tmp_one(t_mini *shell, char *str);
void			add_back(t_mini *shell, t_exec *new);
void			ft_back_lst(t_mini *shell, t_tokenisation *new);
void			*pre_check(t_mini *shell);
void			*ft_organisation(t_mini *shell);
void			*find_last_heredoc(t_mini *shell);
void			*help_organisation(t_mini *shell, int part);
void			you_need_hd(t_mini *shell);
void			child_alone(t_mini *shell);
void			our_child(t_mini *shell);
void			fork_with_us(t_mini *shell);
void			are_you_builtin(t_mini *shell, char **builtin);
void			just_one_process(t_mini *shell);
void			condi(t_mini *shell, char *str, int who);
void			third_condi(t_mini *shell, char *str, int who);
void			second_condi(t_mini *shell, char *str);
void			special_condi(t_mini *shell, char *str, int who);

t_ecosystem		*ft_lstnew(char *content, char *con);
t_exec			*ft_new(t_mini *shell, int i);
t_tokenisation	*ft_new_lst(t_mini *shell, int j, char *str);

#endif
