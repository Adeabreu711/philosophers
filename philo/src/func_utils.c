/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-abr <alde-abr@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 19:27:47 by alde-abr          #+#    #+#             */
/*   Updated: 2025/07/20 15:29:36 by alde-abr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @return A pointer with "elementCount" elements with a "size" size,
 * all values are init to '\0'.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*mem;
	unsigned int	c_size;
	int				i;

	i = -1;
	c_size = nmemb * size;
	if (c_size < nmemb && c_size < size)
		return (NULL);
	mem = malloc(c_size);
	if (!mem)
		return (NULL);
	while (++i < (int)c_size)
		*(unsigned char *)(mem + i) = 0;
	return (mem);
}

/**
 * @brief Copy "n" bytes of the "src" memory area pointed to the "dest" area
 * , pointers can ovelarp.
 * @param {void*} "dest" pointer to the destination memory location (to replace).
 * @param {void*} "src" pointer to the source memory location (to copy).
 * @param {size_t} "n" size.
 * @return The destination memory location ("dest").
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = -1;
	if (!dest && !src)
		return (NULL);
	if (src < dest && dest < src + n)
		while (n-- > 0)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	else
		while (++i < n)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
	return (dest);
}

/**
 * @return A long corresponding to the given string, -1 if above INT limits.
 * @exception The string cannot start with letters, have more than
 * two signs before the numbers or above INT_MAX / INT_MIN
 */
long	ft_atol(const char *nptr)
{
	unsigned int	i;
	long			temp;
	int				sign;

	i = 0;
	temp = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -sign;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		temp = (temp * 10) + nptr[i] - '0';
		i++;
	}
	if (temp > INT_MAX || temp < INT_MIN)
		return (-1);
	return (temp * sign);
}
