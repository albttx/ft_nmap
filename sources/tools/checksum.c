/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 12:26:57 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 10:33:31 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

u_short		csum(u_short *ptr, int nbytes)
{
	register long	sum;
	u_short			oddbyte;
	register short	answer;

	sum = 0;
	while (nbytes > 1)
	{
		sum += *ptr++;
		nbytes -= 2;
	}
	if (nbytes == 1)
	{
		oddbyte = 0;
		*((u_char *)&oddbyte) = *(u_char *)ptr;
		sum += oddbyte;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum = sum + (sum >> 16);
	answer = (short)~sum;
	return (answer);
}
