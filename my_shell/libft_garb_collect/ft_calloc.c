/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:51:49 by monabati          #+#    #+#             */
/*   Updated: 2025/05/24 17:50:32 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size, t_garbage **garb_coll)
{
	unsigned char	*tmp;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	tmp = (unsigned char *) ft_malloc(size * count, garb_coll);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
