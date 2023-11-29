/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:51:33 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/19 01:42:17 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

void	ft_pwd(t_mini *shell)
{
	char	*s;

	s = malloc(sizeof(char) * 110);
	if (!s)
		return ;
	if (shell->all->wordi[0])
	{
		if (shell->all->wordi[0][0] == '-')
		{
			error_message(B_ERR_PWD, shell->all->wordi[0], A_ERR_PWD, 2);
			g_ret_val = 2;
			return ;
		}
	}
	if (!getcwd(s, 100))
		printf("%s\n", get_env("OLDPWD", shell));
	else
		printf("%s\n", getcwd(s, 100));
	free(s);
	g_ret_val = 0;
}
