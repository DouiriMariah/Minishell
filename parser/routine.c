/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 20:52:30 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 02:12:27 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	ft_quota(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((i == 0 || (str[i -1] && str[i - 1] == ' '))
			&& str[i] == '\"' && str[i + 1] && str[i + 1] == '\"'
			&& (!str[i + 2] || (str[i + 2] && str[i + 2] == ' ')))
		{
			str[i] = -str[i];
			str[i + 1] = -str[i + 1];
			i = i + 2;
		}
		else if ((i == 0 || (str[i -1] && str[i - 1] == ' '))
			&& str[i] == '\'' && str[i + 1] && str[i + 1] == '\''
			&& (!str[i + 2] || (str[i + 2] && str[i + 2] == ' ')))
		{
			str[i] = -str[i];
			str[i + 1] = -str[i + 1];
			i = i + 2;
		}
		else
			i++;
	}
}

int	loop_routine(t_mini *shell, char *proc)
{
	ft_quota(proc);
	if (!final_string(proc, shell))
		return (0);
	shell->all = malloc(sizeof(t_exec));
	if (!shell->all)
		return (0);
	shell->old_str = ft_strlen(proc);
	fill_new_str(shell, proc);
	return (1);
}

void	add_process_tokens(t_mini *shell, char *proc_tok, int j)
{
	int	m;

	m = 0;
	while (proc_tok[m])
	{
		if (proc_tok[m] < 0)
			proc_tok[m] = -proc_tok[m];
		m++;
	}
	if (j == 0)
		shell->all->head_process = ft_new_lst(shell, j, proc_tok);
	else
		ft_back_lst(shell, ft_new_lst(shell, j, proc_tok));
}

void	fill_shell_all(t_mini *shell, int i)
{
	t_exec	*tmp;

	shell->all->pos_process = i;
	shell->all->builtin = shell->builtin;
	shell->all->file1 = 0;
	shell->all->file2 = 1;
	shell->builtin = 0;
	shell->all->next = NULL;
	if (i == 0)
		shell->head_all = shell->all;
	else
	{
		tmp = shell->head_all;
		while (tmp->next)
			tmp = tmp->next;
		if (!tmp->next)
			tmp->next = shell->all;
		shell->all = shell->all->next;
	}
}

void	ft_routine(t_mini *shell, int i)
{
	char	**process_tokens;
	int		j;

	i = 0;
	process_tokens = NULL;
	shell->all = NULL;
	while (shell->process[i])
	{
		if (!loop_routine(shell, shell->process[i]))
			return ;
		process_tokens = NULL;
		process_tokens = ft_split_dans_process(shell->final_str, ' ');
		shell->all->head_process = NULL;
		j = -1;
		while (process_tokens[++j])
			add_process_tokens(shell, process_tokens[j], j);
		fill_tokens(shell, j);
		fill_shell_all(shell, i);
		free_double_char(process_tokens);
		free(shell->final_str);
		process_tokens = NULL;
		i++;
	}
}
