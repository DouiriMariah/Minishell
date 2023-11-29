/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:44:47 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/20 01:18:55 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	ft_cd_one(t_mini *shell)
{
	char	*joined;
	char	*export;
	char	*m1;
	char	*m;

	export = ft_strjoin("bash: cd: ", shell->all->wordi[0]);
	m = ft_strjoin(export, ": ");
	free(export);
	joined = ft_strjoin(m, strerror(errno));
	m1 = ft_strjoin(joined, "\n");
	ft_putstr_fd(m1, 2);
	free(m1);
	free(joined);
	free(m);
	g_ret_val = 1;
}

void	ft_cd_two(t_mini *shell, char *old_pwd)
{
	char	*joined;
	char	*m;
	char	**cd;

	cd = malloc(sizeof(char *) * (3));
	if (!cd)
		return ;
	cd[0] = ft_strdup(old_pwd);
	m = malloc(sizeof(char) * 110);
	if (!m)
		return ;
	joined = ft_strjoin("PWD=", getcwd(m, 100));
	cd[1] = ft_strdup(joined);
	free(joined);
	free(m);
	cd[2] = 0;
	ft_export(cd, shell);
	free_double_char(cd);
}

void	ft_cd(t_mini *shell)
{
	char	*s;
	char	*check;
	char	*m;

	if (!shell->all->wordi[0] || shell->all->wordi[1])
	{
		if (!shell->all->wordi[0])
			ft_putstr_fd("bash: cd: requires an absolut or relative path\n", 2);
		else
			ft_putstr_fd("bash: cd: too many arguments\n", 2);
		g_ret_val = 1;
		return ;
	}
	s = malloc(sizeof(char) * 110);
	check = malloc(sizeof(char) * 110);
	if (!s || !check)
		return ;
	m = ft_strjoin("OLDPWD=", getcwd(s, 100));
	if (chdir(shell->all->wordi[0]))
		ft_cd_one(shell);
	else if (!twin_char(s, getcwd(check, 100)))
		ft_cd_two(shell, m);
	free(m);
	free(s);
	free(check);
}
