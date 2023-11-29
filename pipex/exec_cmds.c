/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdouiri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:45:49 by mdouiri           #+#    #+#             */
/*   Updated: 2022/08/22 05:03:14 by amattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_ret_val;

char	*ft_path(char **env)
{
	char	**enva;
	int		i;

	i = 0;
	enva = env;
	while (enva[i] && (ft_str(enva[i], "PATH=") == 0))
		i++;
	if (!enva[i])
		return (NULL);
	return (enva[i] + 5);
}

char	*ft_strjoino(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		v;

	res = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	v = 0;
	while (s1[i])
	{
		res[v] = s1[i];
		i++;
		v++;
	}
	res[v] = '/';
	v++;
	i = -1;
	while (s2[++i])
	{
		res[v] = s2[i];
		v++;
	}
	res[v] = '\0';
	return (res);
}

char	*absolut_command(char *cmd)
{
	if (cmd && access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
		return (NULL);
}

char	*ft_command_exist(char *cmd, char **env)
{
	char	*path;
	char	*path_bis;
	char	*new_path;
	char	*ret;

	if (ft_found_char(cmd, '/') != -1)
		return (absolut_command(cmd));
	path = (ft_path(env));
	while (cmd && path && (ft_found_char(path, ':') != -1))
	{
		path_bis = ft_strdupo(path, ft_found_char(path, ':'));
		new_path = ft_strjoino(path_bis, cmd);
		ret = ft_strdup(new_path);
		if (cmd && access(new_path, X_OK) == 0)
		{
			free(path_bis);
			free(new_path);
			return (ret);
		}
		free(ret);
		free(new_path);
		free(path_bis);
		path = path + (ft_found_char(path, ':') + 1);
	}
	return (NULL);
}

void	ft_exec(t_mini *shell)
{
	char	*good_path;

	good_path = NULL;
	good_path = ft_command_exist(shell->all->wordi[0], shell->envp);
	if (!good_path)
		error_message(B_ERR_CMD, shell->all->wordi[0], A_ERR_CMD1, 2);
	else
	{
		if (execve(good_path, shell->all->wordi, shell->envp) == -1)
		{
			ft_putstr_fd("bash: ", 2);
			perror(shell->all->wordi[0]);
			free(good_path);
		}
	}
}
