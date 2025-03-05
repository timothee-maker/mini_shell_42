/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:26:44 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/15 11:21:42 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_sepa(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	int		j;
	char	*ptr;

	i = 0;
	k = 0;
	j = ft_strlen(s1);
	while (s1[i] && is_sepa(s1[i], set))
		i++;
	if (i == j)
		return (ft_strdup(""));
	while (is_sepa(s1[j - 1], set))
		j--;
	ptr = (char *)malloc(sizeof(char) * ((j - i) + 1));
	if (!ptr || !s1)
		return (NULL);
	while (i < j)
		ptr[k++] = s1[i++];
	ptr[k] = '\0';
	return (ptr);
}

int	is_sepa(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char *str = "   XXX   XXXX";
// 	char *set = " X";
// 	char *ptr;
// 	ptr = ft_strtrim(str, set);
// 	printf("%s\n", ptr);
// 	free(ptr);

// 	return (0);
// }