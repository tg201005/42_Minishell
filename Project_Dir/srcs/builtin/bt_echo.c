/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyi <tyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:36:26 by tyi               #+#    #+#             */
/*   Updated: 2023/01/06 15:47:48 by tyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

extern int	g_last_exit_status;

int	is_proper_opt(char *word, char opt_chr)
{
	int	i;

	i = 1;
	if (word[0] != '-' || ft_strlen(word) < 2)
		return (EX_SUCCESS);
	while (word[i])
	{
		if (word[i] != opt_chr)
			return (EX_SUCCESS);
		i++;
	}
	return (EX_BT_FAIL);
}

int	bt_echo(char **cmd_vector, t_list *envp_list)
{
	int		i;
	int		new_line_flag;

	(void)envp_list;
	new_line_flag = 1;
	i = 1;
	while (cmd_vector[i] && is_proper_opt(cmd_vector[i], 'n'))
	{
		new_line_flag = 0;
		i++;
	}
	while (cmd_vector[i])
	{
		printf("%s", cmd_vector[i]);
		if (!cmd_vector[i + 1])
			break ;
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line_flag == 1)
		printf("\n");
	return (EX_SUCCESS);
}
