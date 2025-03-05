/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:26:41 by tnolent           #+#    #+#             */
/*   Updated: 2024/11/13 11:23:17 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	nb = nb % 10 + '0';
	write(fd, &nb, 1);
}

// int	main()
// {
// 	int	a = -2147483648LL; 
// 	ft_putnbr_fd(a, 1);
// 	return (0);
// }