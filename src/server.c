/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:01:04 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/10 18:36:33 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

/*
    TODO
    SIGUSR1 & SIGUSR2 from server
    I neeed to stablish an handler 
    for these signals
    if SIGUSR1-> BIT 1
    if SIGUSR2-> BIT 0
    Protocol
*/

// This part is need to be include in the utilies files 


void handler(int signal, siginfo_t *info, void *more_info)
{

   (void)more_info;
   static char      c = 0;
   static int       bit = 0;
   static __pid_t   Client = 0;

   if (info->si_pid)
        Client = info->si_pid;
   if (SIGUSR1 == signal)
        c |= (0b10000000 >> bit);
    else if (SIGUSR2 == signal)
        c &= ~(0b10000000 >> bit);
    bit++;
    
    if (CHAR_BIT == bit)
    {
        bit = 0;
        if (c == '\0')
        {
            write(STDOUT_FILENO, "\n", 1);
            Kill(Client, SIGUSR2);
            c = 0;
            return ;
        }
        write(STDOUT_FILENO, &c, 1);
        c = 0;
    }
    Kill(Client, SIGUSR1);
}


int main(void)
{
    int PID;

    PID = getpid();
    ft_printf("PID : %d \n", PID);

    //Wrapper function to KISS(Keep it Simple)
    Signal(SIGUSR1, handler, true);
    Signal(SIGUSR2, handler, true);

    while (252151)
        pause();
    
    return(0);
}
