/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:01:07 by nalfonso          #+#    #+#             */
/*   Updated: 2025/12/13 13:49:33 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

volatile sig_atomic_t g_server = BUSY;

/* void end_handler(int signal)
{
    if (signal == SIGUSR1)
    {
        write(1, "OK\n", 2);
        exit(EXIT_SUCCESS);
    }
}

void ack_handler(int signal)
{
    if (signal == SIGUSR2)
        g_server = READY;
} */

static void	end_handler(int sig)
{
    (void)sig;
	write(STDOUT_FILENO, "\n\tMessage received\n", 19);
	_exit(EXIT_SUCCESS);
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

int main(int ac, char **av)
{
    char *message;
    __pid_t pid;
    int i;
    
    if (ac != 3)
    {
        fputs("Usage = ./client <PID> \"Message\"\n", stderr);
        exit(EXIT_FAILURE);
    }
    
    pid = ft_atoi(av[1]);
    message = av[2];
    
    Signal(SIGUSR1, ack_handler, false);
    Signal(SIGUSR2, end_handler, false);
    i = -1;
    while (message[++i])
        send_char(message[i], pid);
    send_char('\0', pid);
    return (EXIT_SUCCESS);
}

//Include this in utilities.

/* void ft_srtlen(char *str, __pid_t pid)
{
    int i;

    i = -1;
    while (str[++i]);
    
    //Implement here kill Function to send the leng and the allocate the enough s[ace]
     
} */