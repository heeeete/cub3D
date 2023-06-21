/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:41:34 by huipark           #+#    #+#             */
/*   Updated: 2023/06/16 13:46:21 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *find_delim(char *p, const char *delim) {
	while (*p != '\0') {
		const char* d = delim;
		while (*d != '\0') {
			if (*p == *d) {
				*p = 0;
				return (p);
			}
			d++;
		}
		p++;
	}
	return (NULL);
}

char *ft_strtok(char *str, const char *delim) {
	static	char *src;
	char	*p;
	char	*ret;

	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);

	p = find_delim(src, delim);
	if (p) {
		ret = src;
		src = p + 1;
	} else if (*src) {
		ret = src;
		src = NULL;
	} else {
		ret = NULL;
	}

	return (ret);
}
