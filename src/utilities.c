/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 21:00:56 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/10 17:58:32 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minitalk.h"

int ft_atoi(char *nbr)
{
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;
    while((nbr[i] >=9 && nbr[i] <= 13) || nbr[i] == 32)
        i++;
    if (nbr[i] == '+' || nbr[i] == '-')
    {
        if (nbr[i] == '-')
            sign = -sign;
        i++;
    }
    while (nbr[i] >= '0' && nbr[i] <= '9')
    {
        result = result * 10 + (nbr[i] - 48);
        i++;
    }
    return(result * sign);
}

void  Signal(int signo, void *handler, bool use_siginfo)
{
    struct sigaction  sa = {0};

    // Put the handler function inside sigaction
    if (use_siginfo)
    {
        sa.sa_flags = SA_SIGINFO;
        sa.sa_sigaction = handler;
    }
    else
        sa.sa_handler = handler;

    // Block SIGUSR1 whle processing SIGUSR2 and viceversa
    
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);

    //Call the sigaction

    if (sigaction(signo, &sa, NULL) < 0)
    {
        write(2, "Sigaction failed\n", 12);
        exit(EXIT_FAILURE);
    }
}

void Kill(__pid_t pid, int signo)
{
    if (kill(pid, signo) < 0)
    {
        write(2, "Kill Failed\n", 12);
        exit(EXIT_FAILURE);
    }
}