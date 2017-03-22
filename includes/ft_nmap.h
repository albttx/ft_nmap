/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/22 14:57:52 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NMAP_H
# define FT_NMAP_H

# include "libft.h"

# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/ip.h>
# include <netinet/tcp.h>
# include <netinet/ip_icmp.h>
# include <pcap/pcap.h>
# include <pthread.h>
# include <signal.h>

typedef enum			e_type
{
	SYN					= 1,
	NUL					= 2,
	ACK					= 4,
	FIN					= 8,
	XMAS				= 16,
	UDP					= 32,
}						t_type;

typedef struct			s_env
{
	t_list				*ip;
	int					port[2];
	int					thread;
	int					id;
	char				source[INET_ADDRSTRLEN];
	enum e_type			type_flags;
}						t_env;

typedef struct			s_ip
{
	char				*hostname;
	char				*ipv4name;
}						t_ip;

typedef struct			s_pseudo_hdr
{
	unsigned int		src_addr;
	unsigned int		dst_addr;
	unsigned char		placeholder;
	unsigned char		protocol;
	unsigned short		tcp_length;
	struct tcphdr		tcp_h;
}						t_pseudo_hdr;

typedef struct			s_peer
{
	int					sock;
	char				buff[4096];
	struct ip			*iph;
	struct tcphdr		*tcph;
	struct sockaddr_in	dest;
}						t_peer;

t_env				g_env;

char				*hostname_to_ip(const char *hostname);
unsigned short		csum(unsigned short *ptr, int nbytes);

int					parser(char **av);
int					ft_nmap(void);

int					create_socket(void);

void				get_local_ip(char *buffer);

void				scan(t_ip *ip);
void				scan_syn(t_peer *peer);

void				*recv_ack(void *ptr);

void				dbg_print_flags(void);
void				dbg_print_ip(void);
void				dbg_print_port(void);
void				dbg_print_tcp_types(struct tcphdr *tcph);

#endif
