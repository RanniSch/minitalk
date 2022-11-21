/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 05:14:30 by rschlott          #+#    #+#             */
/*   Updated: 2022/11/21 06:04:23 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* Convert a string to an integer. The behavior is the same as 
strtol (The string may begin with an arbitrary amount of white 
space followed by a single optional '+' or '-'  sign.) */
int	ft_atoi(const char *str)
{
	int			sign;
	long int	convert;

	sign = 1;
	convert = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str && *str > 47 && *str < 58)
	{
		convert = (convert * 10) + *str - '0';
		str++;
		if (convert > 2147483647 && sign == 1)
			return (-1);
		if (convert > 2147483648 && sign == -1)
			return (0);
	}
	return (convert * sign);
}

/* counts length of a string */
int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*(s + count) != '\0')
		count++;
	return (count);
}

/* Outputs the string ’s’ to the given file
descriptor. */
void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	char	c;

	i = 0;
	while (*(s + i) != 0)
	{
		c = *(s + i);
		write(fd, &c, 1);
		i++;
	}
}

/* A function that displays the number entered as a parameter. The function
has to be able to display all possible values within an int type variable. */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

/* Outputs the character ’c’ to the given file
descriptor. */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
