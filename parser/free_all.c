/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 02:13:18 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:15:35 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	delete_token(t_tokenisation *start)
{
	t_tokenisation	*temp;

	while (start != NULL)
	{
		temp = start;
		start = start->next;
		free(temp->separated);
		free(temp);
	}
	start = NULL;
}

void	deleteallnodes(t_exec *start)
{
	t_exec	*temp;

	while (start != NULL)
	{
		temp = start;
		start = start->next;
		free_double_char(temp->wordi);
		delete_token(temp->head_process);
		free(temp);
	}
}

void	free_double_char(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str && str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

void	ft_free_env(t_ecosystem *start, t_mini *shell)
{
	int			i;
	t_ecosystem	*tmp;

	tmp = NULL;
	i = 0;
	while (start)
	{
		tmp = start;
		start = start->next;
		if (tmp->tree)
		{
			free(tmp->tree);
			tmp->tree = NULL;
		}
		if (tmp->leaf)
		{
			free(tmp->leaf);
			tmp->leaf = NULL;
		}
		free(tmp);
		if (shell->envp[i])
			free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
}

void	ft_free_test(t_mini *shell)
{
	if (shell->dol)
	{
		free(shell->newi);
		shell->newi = NULL;
	}
	shell->dol = 0;
	deleteallnodes(shell->head_all);
	free_double_char(shell->process);
}
