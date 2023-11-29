/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:04:21 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/19 02:15:54 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	which_type(char *str, int *i, t_mini *shell)
{
	if (*i == 0)
	{
		if (twin_char(str, "echo") || twin_char(str, "cd")
			|| twin_char(str, "pwd") || twin_char(str, "export")
			|| twin_char(str, "unset") || twin_char(str, "env")
			|| twin_char(str, "exit"))
		{
			(*i)++;
			shell->builtin = 1;
			return (BUILTIN);
		}
	}
	if (twin_char(str, ">"))
		return (EXIT);
	else if (twin_char(str, "<"))
		return (ENTRY);
	else if (twin_char(str, ">>"))
		return (EXIT_APPEND);
	else if (twin_char(str, "<<"))
		return (LIMIT);
	(*i)++;
	return (WORD);
}

int	option_n(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] != '-')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

void	change_if_prev(t_tokenisation *tmp, t_mini *shell)
{
	if (tmp->prev)
	{
		if (tmp->prev->type == ENTRY)
			tmp->type = FILE_IN;
		else if (tmp->prev->type == EXIT)
			tmp->type = FILEOUT;
		else if (tmp->prev->type == EXIT_APPEND)
			tmp->type = FILE_APPEND;
		else if (tmp->prev->type == LIMIT)
		{
			tmp->type = HEREDOC;
			shell->nb_heredoc++;
		}
	}
}

void	fill_tokens(t_mini *shell, int j)
{
	t_tokenisation	*tmp;
	int				i;
	int				k;

	tmp = shell->all->head_process;
	i = 0;
	k = 0;
	shell->all->wordi = NULL;
	shell->all->wordi = malloc(sizeof(char *) * (j + 1));
	if (!shell->all->wordi)
		return ;
	while (tmp)
	{
		tmp->type = which_type(tmp->separated, &i, shell);
		change_if_prev(tmp, shell);
		if (tmp->type == WORD)
			shell->all->wordi[k++] = ft_strdup(tmp->separated);
		tmp = tmp->next;
	}
	shell->all->wordi[k] = 0;
}
