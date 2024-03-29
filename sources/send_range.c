/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_range.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:05:23 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/30 15:51:23 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

void	send_range(int sock, int range[], char *destip, enum e_tcp_type flags)
{
	t_peer				peer;
	size_t				len;
	ssize_t				ret;
	t_pseudo_hdr		psh;

	len = sizeof(struct ip) + sizeof(struct tcphdr);
	set_peer(&peer, sock, destip);
	set_ip_header(peer.iph, &peer.dest);
	set_tcp_header(peer.tcph, flags);
	set_pseudo_header(&psh, &peer.dest);

	while (range[0] <= range[1])
	{
		(peer.tcph)->dest = htons(range[0]);
		(peer.tcph)->check = 0;
		psh.dst_addr = (peer.dest).sin_addr.s_addr;
		ft_memcpy(&psh.tcp_h, peer.tcph, sizeof(struct tcphdr));
		(peer.tcph)->check = csum((u_short *)&psh, sizeof(t_pseudo_hdr));

		ret = sendto(sock, (void *)peer.buff, len, 0,
				(struct sockaddr *)&(peer.dest), sizeof(peer.dest));

		if (ret <= 0)
		{
			perror("sendto()");
		}
		range[0] += 1;
	}
}
