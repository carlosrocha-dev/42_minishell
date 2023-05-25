/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_args(const char *arg) // exit 1 a 3
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg == NULL && arg[i] != '\0')
	{
		if (arg[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

int	check_erros_exit(const char *arg, int count)
{
	int result;

	if (count > 1)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (arg[0] != '-' && ft_isdigit(arg[0]) == 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	if (arg[0] == '-' && ft_isdigit(arg[1]) == 1)
	{
		ft_printf("atoi\n");
		result = (exit_code % 256 + 256) % 256
		return (result);
	}
	return (0);
}

int	exit_adapter(const char *arg)
{
	int	count;
	int	exit_code;

	if (arg == NULL)
		return (0);
	count = 0;
	count = count_args(arg);
	ft_printf("arg:%s\n", arg);
	exit_code = check_erros_exit(arg, count);
	exit_code = ;
	return (exit_code);
}
