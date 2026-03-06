# ifndef MINITALK_H
#define MINITALK_H


// Libraries 
# include <unistd.h>
# include <signal.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# define BUSY   0
# define READY  1

// Structure

typedef struct s_state
{
	int			stage;
	__pid_t		client;
	__uint32_t	len;
	__uint32_t	i;
	int			bit;
	char		c;
	char		*msg;
}	t_state;

typedef struct s_client
{
	__pid_t 	pid;
	int			len;
	char		*msg;
}	t_client;

//Printf Function

# define CHEXADECIMAL "0123456789ABCDEF"
# define HEXADECIMAL "0123456789abcdef"

void 	Signal(int sig, void *handler, bool use_siginfo);
void 	Kill(__pid_t pid, int signo);
int 	ft_atoi(char *nbr);
int		ft_strlen(char *str);
void	ft_reset(t_state *s);
void	ft_read_len(t_state *s, int signal);
void	ft_finish(t_state *s);
void	ft_initialize(t_client *c);

typedef unsigned long long	t_number;

int		ft_printf(const char *format, ...);

#endif