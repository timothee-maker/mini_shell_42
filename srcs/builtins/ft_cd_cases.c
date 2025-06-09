/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:29 by lde-guil          #+#    #+#             */
/*   Updated: 2025/05/30 12:27:24 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/minishell.h"

//int	home_case(t_exec *exec, t_env *var)
//{
//	char	*path;
//	int		res;

//	path = ft_strdup(fetch_value("$HOME", exec));
//	if (!path)
//	{
//		ft_putendl_fd("cd: HOME not set", 2);
//		return (2);
//	}
//	if (update_oldpwd(var) == 1)
//	{
//		res = 1;
//		ft_putendl_fd("cd: Couldn't update OLDPWD", 2);
//	}
//	res = chdir(path);
//	update_currpwd(var, path);
//	free(path);
//	return (res);
//}

//int	reverse_case(t_exec *exec, t_env *var)
//{
//	char	*path;
//	int		res;

//	path = ft_strdup(fetch_value("$OLDPWD", exec));
//	if (!path)
//	{
//		ft_putendl_fd("cd: OLDPWD not set", 2);
//		return (2);
//	}
//	if (update_oldpwd(var) == 1)
//	{
//		res = 1;
//		ft_putendl_fd("cd: Couldn't update OLDPWD", 2);
//	}
//	res = chdir(path);
//	update_currpwd(var, path);
//	free(path);
//	return (res);
//}

//int	base_case(t_env *var, char **args)
//{
//	int	res;

//	if (update_oldpwd(var) == 1)
//	{
//		res = 1;
//		ft_putendl_fd("cd: Couldn't update OLDPWD", 2);
//	}
//	res = chdir(args[1]);
//	update_currpwd(var, args[1]);
//	return (res);
//}
