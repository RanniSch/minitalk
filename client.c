/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 05:09:33 by rschlott          #+#    #+#             */
/*   Updated: 2022/11/24 17:56:12 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* send 8x0 to end the string (tell server that its finished) */
void    end_string(int pid)
{
    int num_shifts;

    num_shifts = 0;
    while (num_shifts < 8)
    {
        kill(pid, SIGUSR1);
        usleep(700);
        num_shifts++;
    }
}

/* with the help of my defined mask and the & operator, I can
send a string to the server. */
void	send_signal(int pid, char *str)
{
	int	num_shifts;
	int	i;
	int	mask;

	i = 0;
	while (str[i])
	{
		mask = 0b10000000;
		num_shifts = 0;
		while (num_shifts < 8)
		{
			if ((str[i] & mask) == 0)
			    kill(pid, SIGUSR1);
			else
			    kill(pid, SIGUSR2);
			mask = mask >> 1;
			num_shifts++;
			usleep(700);
		}
        i++;
	}
    end_string(pid);
}

/* receiving signal from server; if no signal "Server PID must be correct" */
static void get_res(int sig)
{
	static int	count;

	if (!count)
		count = 0;
    if (sig == SIGUSR1)
        count++;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Received ", 1);
		ft_putnbr_fd(count, 1);
		ft_putendl_fd(" responses (Signals) from Server.", 1);
		exit(0);
	}
}

/* examines and changes both signals and then sending signal to a process */
int	main(int argc, char **argv)
{
	//struct sigaction	sa;

    //sa = (struct sigaction){.sa_sigaction = get_res};
	//sa.sa_flags = SA_SIGINFO;
	//sigaction(SIGUSR1, &sa, NULL);
	//sigaction(SIGUSR2, &sa, NULL);
    signal(SIGUSR1, &get_res);
	signal(SIGUSR2, &get_res);
	if (argc == 3)
        send_signal(ft_atoi(argv[1]), argv[2]);
    else
		ft_putendl_fd("Insert: ./client [SERVER-PID] [\"STRING\"]", 1);
	//sa.sa_sigaction = get_res;
	return (0);
}
