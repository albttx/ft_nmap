/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-batt <ale-batt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:26:06 by ale-batt          #+#    #+#             */
/*   Updated: 2017/03/23 16:32:25 by ale-batt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nmap.h"

enum e_tcp_type		tcp_to_enum(struct tcphdr *tcph)
{
	enum e_tcp_type		types;

	types = 0;
	if (tcph->syn == 1) types |= SYN;
	if (tcph->ack == 1) types |= ACK;
	if (tcph->fin == 1) types |= FIN;
	if (tcph->rst == 1) types |= RST;
	if (tcph->psh == 1) types |= PSH;
	if (tcph->urg == 1) types |= URG;
	return (types);
}
