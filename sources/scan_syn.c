/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_syn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 15:09:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 14:40:22 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

static void		set_pseudo_header(t_pseudo_hdr *psh, struct sockaddr_in *dest)
{
	ft_bzero(psh, sizeof(*psh));
	psh->src_addr = inet_addr(g_env.source);
	/*psh->dst_addr = (dest->sin_addr).s_addr;*/
	psh->placeholder = 0;
	psh->protocol = IPPROTO_TCP;
	psh->tcp_length = htons(sizeof(struct tcphdr));
}

void	scan_syn(t_peer *peer)
{
	ssize_t				sendret;
	size_t				len;
	int					port;
	t_pseudo_hdr		psh;

	len = sizeof(struct ip) + sizeof(struct tcphdr);

	ft_bzero(&psh, sizeof(psh));
	set_pseudo_header(&psh, &peer->dest);
	for (port = g_env.port[0]; port <= g_env.port[1]; port++)
	{
		(peer->tcph)->dest = htons(port);
		(peer->tcph)->check = 0;
		psh.dst_addr = (peer->dest).sin_addr.s_addr;
		memcpy(&psh.tcp_h, peer->tcph, sizeof(struct tcphdr));
		(peer->tcph)->check = csum((unsigned short *)&psh, sizeof(t_pseudo_hdr));

		sendret = sendto(peer->sock, (void *)peer->buff, len, 0,
				(struct sockaddr *)&peer->dest, sizeof(peer->dest));
		if (sendret == -1)
			perror("sendto()");
		printf("%d: sendret = %ld\n", port, sendret);
	}
}
