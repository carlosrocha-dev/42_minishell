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

int	count_args(const char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg && arg[i] != '\0')
	{
		if (arg[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

int	check_start_dash(const char *arg)
{
	if (arg[0] == '-' && ft_isdigit(arg[1]) == 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	if (arg[0] == '-' && ft_isdigit(arg[1]) == 1)
		return (ft_atoi(arg));
	if (arg[0] == '-' && arg[1] == '\0')
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	return (0);
}

int	check_errors_exit(const char *arg, int count)
{
	int	result;

	if (count > 2)
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (arg == NULL)
		return (0);
	result = check_start_dash(arg);
	if (result != 0)
		return (result);
	if (arg[0] != '-' && ft_isdigit(arg[0]) == 0)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", arg);
		return (2);
	}
	if (arg != NULL)
		return (ft_atoi(arg));
	return (0);
}

int	exit_adapter(t_cmds *cmds)
{
	int	count;
	int	exit_code;

	cmds->signal_exit = 1;
	printf("exit\n");
	if (cmds->current->phrase_parsed == NULL)
		return (0);
	count = count_args(cmds->current->phrase);
	exit_code = check_errors_exit(cmds->current->phrase_parsed[1], count);
	exit_code = (exit_code % 256 + 256) % 256;
	cmds->exit_code.code = exit_code;
	return (exit_code);
}
