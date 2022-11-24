/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:09:37 by rschlott          #+#    #+#             */
/*   Updated: 2022/11/24 17:52:10 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* writes the mask (f.e. one letter) and sends a signal to the client */
void	ft_write_send(pid_t pid, unsigned int mask)
{
    if (!mask)
    {
        ft_putendl_fd("\nMessage Received!", 1);
        kill(pid, SIGUSR2);
    }
    else
    {
        ft_putchar_fd(mask, 1);
        kill(pid, SIGUSR1);
    }
}

/* receives signal from client and transforms with the help of
each signal (8 in total) from one mask, the mask back into f.e. one letter. 
static means, it continues where it stopped
(it exists till the end of the program once initialized). Mask and 
num_shifts are only = 0 before 8 bits arrive. */
static void receive_signal(int sig, siginfo_t *siginfo, void *context)
{
	static int				num_shifts;
	static unsigned int     mask;

	(void)context;
    if (!mask)
        mask = 0;
    if (!num_shifts)
    {
        num_shifts = 0;
    }        
	if (num_shifts < 8)
	{
		if (sig == SIGUSR1)
			mask |= 0;
		else if (sig == SIGUSR2)
            mask |= 1;
	}
    num_shifts++;
	if (num_shifts >= 8)
    {
        ft_write_send(siginfo->si_pid, mask);
        num_shifts = 0;
        mask = 0;
    }
    else
        mask <<= 1;
}

/* this function handles the signal SIGINT (control + c),
	so that if user terminates the program,
it writes a message. */
static void handle_end(int sig, siginfo_t *siginfo, void *ptr)
{
	(void)sig;
	(void)siginfo;
	(void)ptr;
	ft_putendl_fd("\nProgram terminated by user!", 1);
	exit(0);
}

/* struct declared and in it two more things defined. With the SA_SIGINFO flag,
the signals are queued, and they're all delivered. Kill is starting process
to use a signal. For this specific process (with this process ID) function is
called through signal. Who I want to send the message to (kill function with 
the PID and signal) and after what I want to send. */
int	main(void)
{
	struct sigaction	sa;
	struct sigaction	terminate;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
    sa = (struct sigaction){.sa_sigaction = receive_signal};
    sa.sa_flags = SA_SIGINFO;
    terminate = (struct sigaction){.sa_sigaction = handle_end};
    terminate.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	sigaction(SIGINT, &terminate, NULL);
	//sa.sa_sigaction = receive_signal;
	//terminate.sa_sigaction = handle_end;
	while (1)
		pause();
	return (0);
}
