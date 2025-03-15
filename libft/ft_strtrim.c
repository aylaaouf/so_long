/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aylaaouf <aylaaouf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:53:17 by aylaaouf          #+#    #+#             */
/*   Updated: 2024/11/09 20:41:36 by aylaaouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		s;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	s = 0;
	while (s1[start] && ft_check(s1[start], set))
		start++;
	while (end >= start && ft_check(s1[end], set))
		end--;
	if (end < start)
		return (ft_strdup(""));
	str = (char *)malloc(end - start + 2);
	if (!str)
		return (NULL);
	while (start <= end)
	{
		str[s++] = s1[start++];
	}
	str[s] = '\0';
	return (str);
}
