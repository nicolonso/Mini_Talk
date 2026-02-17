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

/**
 * ack_handler - Handles server's acknowledgment signals
 * @sig: Signal number (unused)
 */
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
        //Bitwise Operations
        // A -> 01000001
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
	//ft_printf("number = %d\n", n);
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
    char *message;
    __pid_t pid;
    int i;
	int len;
    
    if (ac != 3)
    {
        write(2, "Usage = ./client <PID> \"Message\"\n", 33);
        exit(EXIT_FAILURE);
    }
    if (!av[2])
		return (EXIT_FAILURE);
    pid = ft_atoi(av[1]);
    if (pid <= 0)
        return (EXIT_FAILURE);
    message = av[2]; // Handle this ""
    len = ft_strlen (message);
	if (len == 0)
	{
		write(2, "Send the correct message\n", 26);
		exit (EXIT_FAILURE);
	}
    Signal(SIGUSR1, ack_handler, false);
    Signal(SIGUSR2, end_handler, false);
    i = -1;
	send_int(len, pid);
    while (message[++i])
        send_char(message[i], pid);
    return (EXIT_SUCCESS);
}

