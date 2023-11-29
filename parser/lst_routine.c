/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:22:32 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/23 16:22:36 by mdouiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenisation	*ft_new_lst(t_mini *shell, int j, char *str)
{
	t_tokenisation	*new;

	(void)shell;
	new = malloc(sizeof(t_tokenisation));
	if (!new)
		return (NULL);
	new->separated = NULL;
	new->separated = ft_strdup(str);
	new->type = WORD;
	new->position = j;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_back_lst(t_mini *shell, t_tokenisation *new)
{
	t_tokenisation	*tmp;

	tmp = shell->all->head_process;
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

t_exec	*ft_new(t_mini *shell, int i)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->pos_process = i;
	new->builtin = shell->builtin;
	shell->builtin = 0;
	new->next = NULL;
	return (new);
}

void	add_back(t_mini *shell, t_exec *new)
{
	t_exec	*tmp;

	tmp = shell->head_all;
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp->next)
		tmp->next = new;
}
