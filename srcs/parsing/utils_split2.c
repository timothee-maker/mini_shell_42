/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:25:14 by lde-guil          #+#    #+#             */
/*   Updated: 2025/07/21 15:17:05 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_fill_list(t_split_parse *split, char *s, int len_tab)
{
	int	i;

	i = 0;
	while (s[i])
		add_char(split, s[i++]);
	if (len_tab > 1)
		flush_buffer(split);
}
