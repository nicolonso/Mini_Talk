/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:15:58 by nalfonso          #+#    #+#             */
/*   Updated: 2025/09/16 21:23:16 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdr/mini_talk.h"

void signal_handler(int signal)
{
	static int	bit_count = 0;
	static char	characther = 0;
	
	if (signal == SIGUSR1)
		characther |= (0 << bit_count);
	else if (signal == SIGUSR2)
		characther |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write (1, &characther, 1);
		bit_count = 0;
		characther = 0;
	}
}



int main(void)
{
	return (0);
}