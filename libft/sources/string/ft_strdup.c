/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: world42 <world42@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 14:59:05 by world42           #+#    #+#             */
/*   Updated: 2017/03/14 20:57:22 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*s2;
	size_t		len;

	len = ft_strlen(s1);
	s2 = ft_strnew(len + 1);
	ft_strcpy(s2, s1);
	return (s2);
}

char	*ft_strfdup(char *s1)
{
	char		*s2;

	s2 = ft_strdup(s1);
	free(s1);
	return (s2);
}
