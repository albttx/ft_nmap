/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/25 10:32:35 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"
#include <poll.h>

static void		set_in_list(t_list *port_lst, int port, enum e_tcp_type types)
{
	t_list	*tmp;
	t_port	*p_port;

	tmp = port_lst;
	while (tmp)
	{
		p_port = tmp->content;
		if (p_port->port == port)
		{
			p_port->syn_state = syn_set(types);
			p_port->ack_state = ack_set(types);
			p_port->fin_state = syn_set(types);
			break ;
		}
		tmp = tmp->next;
	}
}

static void		process_return(t_list *port_lst, char buff[], ssize_t size)
{
	struct ip			*iph;
	u_short				iplen;
	struct tcphdr		*tcph;
	struct sockaddr_in	src;
	struct sockaddr_in	dst;

	/*printf("recv %ld ", size);*/
	iph = (struct ip *)buff;
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		tcph = (struct tcphdr *)(buff + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		printf("port %d ", ntohs(tcph->source));
		set_in_list(port_lst, ntohs(tcph->source), tcp_to_enum(tcph));
		dbg_print_tcp_types(tcph);
	}
	else
		printf("\n");
}

static void		listening_socket(t_list *port_lst)
{
	int					sock;
	char				buff[65536];
	struct sockaddr_in	from;
	socklen_t			fromlen;
	ssize_t				ret;
	struct pollfd		pfd[1];
	nfds_t				ndfs;
	int					timeout;

	puts("start thread");
	fromlen = sizeof(from);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (sock == -1)
	{
		perror("recv sock");
		exit(EXIT_FAILURE);
	}

	ndfs = 1;
	timeout = 2 * 60 * 60; // 2 sec
	pfd[0].fd = sock;
	pfd[0].events = POLLIN;
	pfd[0].revents = 0;

	while (42)
	{
		ft_bzero(&from, sizeof(from));
		ft_bzero(buff, sizeof(buff));
		puts("wait to recv...");
		if (poll(pfd, ndfs, timeout) > 0)
		{
			if (pfd[0].revents == POLLERR)
			{
				perror("poll() revents == POLLERR");
				break ;
			}
			ret = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen);
			process_return(port_lst, buff, ret);
		}
		else
			break ;
	}
	close(sock);
	pthread_exit(NULL);
}

void	callback(u_char *ptr, const struct pcap_pkthdr *pkthdr, const u_char *pkt)
{
	struct ether_header		*ethh;
	struct ip				*iph;
	struct tcphdr			*tcph;
	u_short					iplen;
	struct sockaddr_in		src;
	struct sockaddr_in		dst;

	ethh = (struct ether_header *)pkt;
	iph = (struct ip *)(pkt + sizeof(struct ether_header));
	if (iph->ip_p == IPPROTO_TCP)
	{
		iplen = iph->ip_hl * 4;
		if (iplen < 20)
		{
			printf("ERROR: iplen = %d bytes, packet too small\n", iplen);
			return ;
		}
		tcph = (struct tcphdr *)((void *)pkt + sizeof(*ethh) + iplen);
		ft_bzero(&src, sizeof(src));
		ft_bzero(&dst, sizeof(dst));
		src.sin_addr = iph->ip_src;
		dst.sin_addr = iph->ip_dst;
		if (ntohs(tcph->source) == 43591) return ;
		printf("port %d ", ntohs(tcph->source));
		printf(" From: %s To: %s\n", inet_ntoa(iph->ip_src), inet_ntoa(iph->ip_dst));
		/*set_in_list(port_lst, ntohs(tcph->source), tcp_to_enum(tcph));*/
		dbg_print_tcp_types(tcph);
	}
	/*printf("Receive pkt size %d\n", pkthdr->len);*/

}

static void		listening_pcap(t_list *port_lst)
{
	char	errbuff[PCAP_ERRBUF_SIZE];
	pcap_t	*handler;

	handler = pcap_open_live("eth0", 65536, 1, 0, errbuff);
	if (handler == NULL)
	{
		perror("pcap_open_live");
		exit(EXIT_FAILURE);
	}
	if (pcap_dispatch(handler, 1024, callback, NULL) == -1)
	{
		pcap_perror(handler, "pcap_dispatch");
	}
	pthread_exit(NULL);
}

void			*listener(void *ptr)
{
	/*listening_socket(ptr);*/
	listening_pcap(ptr);
	return (NULL);
}
