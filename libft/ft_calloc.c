/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:25:08 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 16:25:14 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, size * count);
	return (ptr);
}
// int    main()
// {
//     char    *ptr;
//     char    *ptr2;
//     char    *ptr3;
//     int    i;

//     i = 0;
//     ptr = ft_calloc(6, sizeof(char));
//     ptr2 = calloc(6, sizeof(char));
//     ptr3 = malloc(sizeof(char) * 6);
//     /*
//     while (i < 5)
//     {
//         ptr[i] = 'J';
//         printf("%c\n", ptr[i]);
//         i++;
//     }
//     ptr[i] = '\0';
//     */
//     free(ptr);
//     free(ptr2);
//     free(ptr3);
//     return (0);
// }