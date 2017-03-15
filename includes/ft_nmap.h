/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/15 18:22:46 by ale-batt         ###   ########.fr       */
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
# include <netinet/ip_icmp.h>
# include <pcap/pcap.h>

# include <signal.h>

typedef enum		e_type
{
	SYN				= 1,
	NUL				= 2,
	ACK				= 4,
	FIN				= 8,
	XMAS			= 16,
	UDP				= 32,
}					t_type;

typedef struct		s_env
{
	t_list			*ip;
	int				port[2];
	int				thread;
	enum e_type		type_flags;
}					t_env;

typedef struct		s_ip
{
	char			*hostname;
	char			*ipv4name;
}					t_ip;

t_env				g_env;

char				*hostname_to_ip(const char *hostname);

int					parser(char **av);
int					ft_nmap(void);

void				dbg_print_flags(void);
void				dbg_print_ip(void);

#endif
