/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:58:35 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/19 00:41:43 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

t_ecosystem	*ft_lstnew(char *content, char *con)
{
	t_ecosystem	*new;

	new = malloc(sizeof(t_ecosystem));
	if (!(new))
		return (NULL);
	new->tree = content;
	new->leaf = con;
	new->next = NULL;
	return (new);
}

void	ft_lst_add_back(t_mini *shell, t_ecosystem *new)
{
	t_ecosystem	*tmp;

	tmp = shell->head;
	while (tmp->next)
		tmp = tmp->next;
	if (!tmp->next)
		tmp->next = new;
}
