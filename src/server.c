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

void handler(int signal, siginfo_t *info, void *more_info)
{
	(void)more_info;
	static int stage = 0;
	static __pid_t client = 0;
	static __uint32_t	len = 0;
	static __uint32_t	i = 0;
	static int bit = 0;
	static char c = 0;
	static char *msg = NULL;

	if (info->si_pid)
		client = info->si_pid;
	if (stage == 0)
	{
		if (SIGUSR1 == signal)
			len |= (0x80000000u >> bit);
		bit++;
		if (bit == 32)
		{
			msg = malloc((size_t)len + 1);
			if (!msg)
			{
				stage = 0;
				len = 0;
				bit = 0;
				return ;
			}
			msg[len] = '\0';
			i = 0;
			stage = 1;
			bit = 0;
		}
	}
	else
	{
		// if (len == 0)
		// {
		// 	write(1, "\n", 1);
    	// 	Kill(client, SIGUSR2);   // tell client done
    	// 	// reset state
   	 	// 	stage = 0;
		// 	len = 0;
		// 	bit = 0;
		// 	client = 0;
		// 	return;
		// }
		if (signal == SIGUSR1)
			c |= (0x80 >> bit);
		else if (SIGUSR2 == signal)
        	c &= ~(0b10000000 >> bit);
		bit++;
		if (CHAR_BIT == bit)
		{
			msg[i++] = c;
			c = 0;
			bit = 0;
			if (i == len)
			{
				write(1, msg, len);
				write(1, "\n", 1);
				free(msg);
				msg = NULL;
				stage = 0;
				len = 0;
				bit = 0;
				Kill (client,SIGUSR2);
				return ;
			}
		}
	}
	Kill (client,SIGUSR1);
}

/* void handler(int signal, siginfo_t *info, void *more_info)
{

   (void)more_info;
   static char      c = 0;
   static int       bit = 0;
   static __pid_t   Client = 0;
   int key = 0;
   char *message;

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
} */


int main(void)
{
    __pid_t PID;

    PID = getpid();
    ft_printf("PID : %d \n", PID);

    //Wrapper function to KISS(Keep it Simple)
    Signal(SIGUSR1, handler, true);
    Signal(SIGUSR2, handler, true);
	//ft_printf("test\n");
    while (252151)
        pause();
    
    return(0);
}

// ------------------------------------------------------ Notes--------------------------------------------------------------------------------------
/* Now is workin with the exception of the emoticons, so basically what I need to now is change the approach of my fft_strlen, and not send an integer instead of
char by char 

It isnt workingwhen i send "" , I nned to handle thta in my client or in my server ???
that is a good a question
I need to review  muy str len 
 */