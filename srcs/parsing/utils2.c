/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:43:31 by tnolent           #+#    #+#             */
/*   Updated: 2025/05/19 16:28:49 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2(char *str1, char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i])
	{
		j = 0;
		while (str2[j])
		{
			if (str1[i] == str2[j++])
				return (1);
		}
		i++;
	}
	return (0);
}

void	empty_string_case(char *split, t_list *list, t_token *token)
{
	if (ft_strlen(split) == 0)
		return ;
	free(token->split->str);
	add_token(list, "ARG", token);
}

void	init_token(t_token *token)
{
	token->position = 0;
	token->redir = 0;
}

// char	*remove_quotes_around(char *str)
// {
// 	char	*new_str;
// 	char	tmp_quote;
// 	size_t	i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	tmp_quote = 0;
// 	if (!ft_strchr2(QUOTES, str))
// 		return (ft_strdup(str));
// 	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
// 	if (!new_str || !str)
// 		return (NULL);
// 	while (str[i])
// 	{
// 		if (ft_strchr(QUOTES, str[i]))
// 			tmp_quote = str[i++];
// 		while (str[i])
// 		{
// 			if (str[i] == tmp_quote)
// 				break ;
// 			if (ft_strchr(QUOTES, str[i]) && (tmp_quote == 0))
// 				tmp_quote = str[i++];
// 			if (str[i] == tmp_quote || !(str[i]))
// 				break ;
// 			new_str[j++] = str[i++];
// 		}
// 		if (!str[i])
// 			break ;
// 		i++;
// 		tmp_quote = 0;
// 	}
// 	return (new_str[j] = '\0', new_str);
// }

// int	check_valid_dollar(char *split)
// {
// 	int		i;
// 	char	tmp;

// 	tmp = 0;
// 	i = 0;
// 	if (split[0] == '$')
// 		return (1);
// 	while (split[i])
// 	{
// 		if (tmp == split[i])
// 			tmp = 0;
// 		if (ft_strchr(QUOTES, split[i]))
// 			tmp = split[i];
// 		if (split[i] == '$' && (tmp == '\"' || tmp == 0))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }
