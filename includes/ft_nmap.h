/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 18:17:35 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/14 20:25:22 by ale-batt         ###   ########.fr       */
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

# include <signal.h>

typedef struct		s_env
{
	t_list			*ip;
	int				port[2];
}					t_env;

typedef struct		s_ip
{
	char			*hostname;
	char			*ipv4name;
}					t_ip;

t_env				g_env;

char				*hostname_to_ip(const char *hostname);

int					parser(char **av);
void				parse_file(char *arg);

#endif
