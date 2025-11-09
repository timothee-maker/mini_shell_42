/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timothee <timothee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:14:35 by lde-guil          #+#    #+#             */
/*   Updated: 2025/11/09 22:40:37 by timothee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_custom_join(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*res;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = ft_calloc((len_s1 + len_s2 + 1), sizeof(char));
	if (!res)
		return (0);
	ft_strlcpy(res, s1, len_s1 + 1);
	ft_strlcat(res, s2, len_s1 + len_s2 + 1);
	free((char *) s1);
	return (res);
}

int	is_special_str(char *str)
{
	if (str[0] == 2)
		return (1);
	return (0);
}

char	*remove_special_str(char *str)
{
	char	*temp;
	char	*old;

	if (is_special_str(str))
	{
		old = str;
		str++;
		temp = ft_strdup(str);
		free(old);
		return (temp);
	}
	return (str);
}

