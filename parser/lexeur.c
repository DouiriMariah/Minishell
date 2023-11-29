/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amattei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:45:38 by amattei           #+#    #+#             */
/*   Updated: 2022/08/23 02:14:35 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	good_pipe(char *str, int i)
{
	int	b;

	b = i - 1;
	if (i == 0 && str[i] != '|')
	{	
		ft_putstr_fd(ERR_CHEV_PIPE1, 2);
		return (-1);
	}
	while (b != 0 && pipo(str[b]) == 1 && !chevron(str[b]))
		b--;
	if ((b == 0 && str[b] == ' ') || chevron(str[b]))
	{
		ft_putstr_fd(ERR_CHEV_PIPE2, 2);
		return (-1);
	}
	b = i + 1;
	while ((pipo(str[b]) == 1) && str[b])
		b++;
	if (!(!pipo(str[b]) && str[b]))
	{
		ft_putstr_fd(ERR_CHEV_PIPE1, 2);
		return (-1);
	}
	return (0);
}

int	check_chevron(char *str, int i)
{
	int	b;

	if (str[i] == str[i + 1])
		i++;
	b = i + 1;
	while (str[b] && pipo(str[b]) == 1)
		b++;
	if (!str[b] || pipo(str[b]) == 2 || chevron(str[b]))
	{
		if (pipo(str[b]) == 2)
			ft_putstr_fd(ERR_CHEV_PIPE1, 2);
		else if (!str[b])
			ft_putstr_fd(ERR_CHEV_NEWLINE, 2);
		return (-1);
	}
	return (0);
}

int	good_number_chevron(char *str, int i)
{
	int	a;

	a = i + 2;
	while (i != a && str[i] == str[i + 1])
		i++;
	if (i < a && str[a - 2] == str[a - 1] && !chevron(str[a]))
		return (0);
	else if ((str[a - 2] && chevron(str[a - 2]) && !str[a - 1])
		|| (str[a - 1] && chevron(str[a - 1]) == 0
			&& chevron(str[a - 2]) && !chevron(str[a])))
		return (0);
	else
	{
		ft_putstr_fd(ERR_CHEV_NEWLINE, 2);
		return (-1);
	}
	return (0);
}

int	quote(char *str, int *i)
{
	int	j;

	j = (*i) + 1;
	while (str[j] && str[j] != str[(*i)])
		j++;
	if (!str[j])
		return (printf(" %c are not closed \n", str[(*i)]), -1);
	(*i) = j + 1;
	return (*i);
}

char	*ft_check_pipe(char *str, t_mini *shell)
{
	shell->i = -1;
	if (!str)
		return (NULL);
	while (++shell->i <= ft_strlen(str) && str[shell->i])
	{
		if ((str[shell->i] == '\'' || str[shell->i] == '\"'))
		{
			if (quote(str, &shell->i) == -1)
				return (NULL);
			shell->i--;
		}
		else if (chevron(str[shell->i]))
		{
			if (good_number_chevron(str, shell->i)
				|| check_chevron(str, shell->i))
				return (NULL);
		}
		else if (str[shell->i] == '|')
		{
			shell->nb_process++;
			if (good_pipe(str, shell->i))
				return (NULL);
		}
	}
	return ("good");
}
