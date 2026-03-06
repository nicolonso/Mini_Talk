/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:01:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/10 18:20:41 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

volatile sig_atomic_t g_server = BUSY;

static void	end_handler(int sig)
{
    (void)sig;
	write(STDOUT_FILENO, "\n\tMessage received\n", 19);
	exit(EXIT_SUCCESS);
}

static void	ack_handler(int sig)
{
    (void)sig;
	g_server = READY;
}

void    send_char(char c, __pid_t pid)
{
    int bit;
    
    bit = 0;
    
    while (bit < CHAR_BIT)
    {
        if (c & (0X80 >> bit))
            Kill(pid, SIGUSR1);
        else
            Kill(pid, SIGUSR2);
        bit++;

        while (BUSY == g_server)
            usleep(42);
        
        g_server = BUSY;
    }
}

void send_int(int n, __pid_t pid)
{
	__uint32_t	x;
	int			bit;

	x = n;
	bit = 0;
	while (bit < 32)
	{
		if (x & (0x80000000u >> bit))
            Kill(pid, SIGUSR1);
        else
            Kill(pid, SIGUSR2);
        bit++;
        while (BUSY == g_server)
            usleep(42);
        g_server = BUSY;
	}
}

int main(int ac, char **av)
{
	t_client c;
	int i;

    if (ac != 3)
    {
		write(2, "Usage = ./client <PID> \"Message\"\n", 33);
        exit(EXIT_FAILURE);
    }
    if (!av[2])
		return (EXIT_FAILURE);
	ft_initialize(&c);
	if (ft_parsing(&c, av[1], av[2]))
		return (EXIT_FAILURE);
    Signal(SIGUSR1, ack_handler, false);
    Signal(SIGUSR2, end_handler, false);
    i = -1;
	send_int(c.len, c.pid);
    while (c.msg[++i])
        send_char(c.msg[i], c.pid);
    return (EXIT_SUCCESS);
}
