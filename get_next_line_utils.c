/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:18:07 by yasser            #+#    #+#             */
/*   Updated: 2023/11/23 15:30:07 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strcat(char *joined, char const *prefix, char const *suffix)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prefix[i] != '\0')
	{
		joined[i] = prefix[i];
		i++;
	}
	while (suffix[j] != '\0')
	{
		joined[i] = suffix[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size1;
	int		size2;
	char	*joined_str;

	size1 = ft_strlen((char *)s1);
	size2 = ft_strlen((char *)s2);
	joined_str = (char *)malloc(size1 + size2 + 1);
	if (joined_str == NULL)
		return (NULL);
	else
		return (ft_strcat(joined_str, s1, s2));
}
