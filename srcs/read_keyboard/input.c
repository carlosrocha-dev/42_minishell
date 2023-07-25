/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_empty(t_cmds *cmds)
{
	char	*clean_phrase;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean_phrase = ft_calloc(ft_strlen(cmds->input->datacpy) + 1, sizeof(char));
	while (cmds->input->datacpy[i] != '\0')
	{
		if (cmds->input->datacpy[i] != ' ')
		{
			clean_phrase[j] = cmds->input->datacpy[i];
			j++;
		}
		i++;
	}
	clean_phrase[j] = '\0';
	free(clean_phrase);
}

char	*remove_duplicate_spaces(char *input_string)
{
	int		i;
	int		j;
	char	*clean_phrase;

	i = 0;
	j = 0;
	clean_phrase = (char *)malloc(strlen(input_string) + 1);
	while (input_string[i] != '\0')
	{
		if (input_string[i] != ' ')
		{
			clean_phrase[j] = input_string[i];
			j++;
		}
		else if (input_string[i + 1] != ' ')
		{
			clean_phrase[j] = input_string[i];
			j++;
		}
		i++;
	}
	clean_phrase[j] = '\0';
	return (clean_phrase);
}

int	check_quotes(t_cmds *cmds)
{
	int	i;
	int	count_simple_quotes;
	int	count_double_quotes;

	i = 0;
	count_simple_quotes = 0;
	count_double_quotes = 0;
	if (cmds->input->datacpy == NULL)
		return (0);
	while (cmds->input->datacpy[i] != '\0')
	{
		if (cmds->input->datacpy[i] == '\'')
			count_simple_quotes++;
		if (cmds->input->datacpy[i] == '\"')
			count_double_quotes++;
		i++;
	}
	if (count_simple_quotes % 2 != 0 || count_double_quotes % 2 != 0)
	{
		printf("Error: quotes not closed\n");
		return (1);
	}
	if (count_simple_quotes > 0 || count_double_quotes > 0)
		cmds->has_quote = 1;
	return (0);
}

void	extract_input_values(t_cmds *cmds)
{
	cmds->input->cmd_name = cmds->input->datacpy;
}

int	read_keyboard(t_cmds *cmds)
{
	load_signals();
	cmds->input->datacpy = readline("\033[0;32mminishell: > \033[0;0m");
	if (cmds->input->datacpy == NULL)
	{
		cmds->input->datacpy = ft_strdup("exit");
		cmds->signal_exit = 1;
		return (0);
	}
	if (ft_strlen(cmds->input->datacpy) == 0)
		return (1);
	add_history(cmds->input->datacpy);
	extract_input_values(cmds);
	if (check_quotes(cmds))
		return (1);
	return (0);
}
