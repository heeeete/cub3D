/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:22:23 by huipark           #+#    #+#             */
/*   Updated: 2022/08/10 19:42:48 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char	*s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == 0)
		return ((char *)s + len);
	while (len > 0)
	{
		if (s[--len] == (char)c)
			return ((char *)s + len);
	}
	return (0);
}
