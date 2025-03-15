/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:47:29 by aylaaouf          #+#    #+#             */
/*   Updated: 2025/03/15 07:32:30 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_l(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
		{
			return ((char *)(&s[i]));
		}
		i++;
	}
	if ((unsigned char)s[i] == (unsigned char)c)
		return ((char *)(&s[i]));
	return (NULL);
}
