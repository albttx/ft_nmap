/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_ack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:46:54 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/24 15:20:07 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

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
	unsigned short		iplen;
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

static void	listening(t_list *port_lst)
{
	int					sock;
	char				buff[65536];
	struct sockaddr_in	from;
	socklen_t			fromlen;
	ssize_t				ret;
	fd_set				fds;
	struct timeval		wait;

	puts("start thread");
	fromlen = sizeof(from);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if (sock == -1)
	{
		perror("recv sock");
		exit(EXIT_FAILURE);
	}
	FD_ZERO(&fds);
	FD_SET(sock, &fds);
	wait.tv_sec = 3;
	wait.tv_usec = 500;
	while (42)
	{
		ft_bzero(&from, sizeof(from));
		ft_bzero(buff, sizeof(buff));
		puts("wait to recv...");
		if (select(sock + 1, &fds, (fd_set *)0, (fd_set *)0, &wait) > 0)
		{
			ret = recvfrom(sock, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen);
			process_return(port_lst, buff, ret);
		}
		else
			break ;
	}
	close(sock);
	pthread_exit(NULL);
}

void		*listener(void *ptr)
{
	listening(ptr);
	return (NULL);
}
