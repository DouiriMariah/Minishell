/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:08:54 by amattei           #+#    #+#             */
/*   Updated: 2022/08/22 04:34:01 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_ret_val;

void	init_dato(t_mini *shell)
{
	shell->pipe_fd[0] = 0;
	shell->pipe_fd[1] = 0;
}

void	reinit(char *str, t_mini *shell)
{
	shell->nb_heredoc = 0;
	shell->nb_process = 0;
	shell->nb_process = total_len_dans_process(str, '|');
	shell->process = NULL;
	shell->heredoc_tab = NULL;
	shell->process = ft_split_dans_process(str, '|');
	shell->builtin = 0;
	shell->final_str = NULL;
	shell->i = 0;
	shell->j = 0;
	shell->v = 0;
	shell->after = 0;
	shell->before = 0;
	shell->newi = NULL;
	init_dato(shell);
}

int	minishell(char *str, t_mini *shell, int i)
{
	reinit(str, shell);
	ft_routine(shell, i);
	if (!shell->all && shell->nb_process == 1)
		free_double_char(shell->process);
	else
	{
		ft_organisation(shell);
		ft_free_test(shell);
	}
	return (0);
}

int	check_str(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] <= 32 || str[i] >= 127)
			check++;
		i++;
	}
	if (i == check)
		return (0);
	else
		return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*str;
	t_mini	shell;
	int		i;

	str = NULL;
	(void)ac;
	(void)av;
	init_data(env, &shell);
	while (1)
	{
		i = -1;
		run_signals(1);
		str = readline(">$ ");
		if (!str)
			break ;
		if (check_str(str))
		{
			add_history(str);
			if (ft_check_pipe(str, &shell))
				minishell(str, &shell, i);
			else
				g_ret_val = 2;
		}
	}
	return (free_exit(&shell), 0);
}
