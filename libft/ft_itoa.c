/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:19:19 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/21 11:12:04 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		number_digit(int nb);
char	*ft_strrev(char *str);
char	*ft_strnew(size_t size);

char	*ft_itoa(int n)
{
	int		j;
	char	*ptr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	j = number_digit(n) + (n < 0);
	ptr = ft_strnew(j);
	if (!ptr)
		return (NULL);
	ptr[j] = '\0';
	if (n == 0)
		ptr[--j] = '0';
	if (n < 0)
	{
		ptr[0] = '-';
		n = -n;
	}
	while (n)
	{
		ptr[--j] = (n % 10) + '0';
		n = n / 10;
	}
	return (ptr);
}

int	number_digit(int nb)
{
	int	i;

	i = 1;
	if (nb < 0)
		nb = -nb;
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_strnew(size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	ft_memset(ptr, '\0', size + 1);
	return (ptr);
}

// int	main(void)
// {
// 	char *ptr;
// 	ptr = ft_itoa(-10000);
// 	printf("%s\n", ptr);
// 	free(ptr);
// 	return (0);
// }