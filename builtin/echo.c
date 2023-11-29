/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:44:57 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 04:58:36 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

int	size_wordi(t_mini *shell)
{
	int		i;
	int		j;
	int		ret;
	char	**tmp;

	i = 0;
	j = 0;
	ret = 0;
	tmp = shell->all->wordi;
	while (tmp && tmp[i])
	{
		j = 0;
		while (tmp && tmp[i][j])
		{
			ret++;
			j++;
		}
		ret++;
		i++;
	}
	return (ret);
}

char	*fill_echo(t_mini *shell, int i)
{
	char	*tmp;
	int		v;
	int		j;

	v = 0;
	tmp = malloc(sizeof(char) * (size_wordi(shell) + 1));
	if (!tmp)
		return (NULL);
	while (shell->all->wordi[i])
	{
		j = 0;
		if (i > 0)
			tmp[v++] = ' ';
		if (twin_char(shell->all->wordi[i], "\"\"")
			|| twin_char(shell->all->wordi[i], "\'\'"))
			;
		else
		{
			while (shell->all->wordi[i][j])
				tmp[v++] = shell->all->wordi[i][j++];
		}
		i++;
	}
	tmp[v] = '\0';
	return (tmp);
}

void	ft_echo(t_mini *shell)
{
	int		option;
	int		i;
	char	*res;
	char	*joined;

	i = 0;
	while (shell->all->wordi[i])
	{
		if (option_n(shell->all->wordi[i]))
			i++;
		else
			break ;
	}
	option = i;
	res = fill_echo(shell, i);
	if (!option)
	{
		joined = ft_strjoin(res, "\n");
		ft_putstr_fd(joined, 1);
		free(joined);
	}
	else
		ft_putstr_fd(res, 1);
	free(res);
	g_ret_val = 0;
}
