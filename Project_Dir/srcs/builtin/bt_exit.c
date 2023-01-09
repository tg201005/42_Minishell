/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyi <tyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 17:35:08 by tyi               #+#    #+#             */
/*   Updated: 2023/01/09 21:46:11 by minseok2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include <unistd.h>

void	ft_error_manage(int	*flag)
{
	*flag = 1;
}

void	init_atoi_data(int	*sign, unsigned long *res, int *i)
{
	*sign = 1;
	*res = 0;
	*i = 0;
}

int	bt_atoi(const char *str, int *flag)
{
	unsigned long	res;
	int				sign;
	int				i;

	init_atoi_data(&sign, &res, &i);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i ++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		ft_error_manage(flag);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = 10 * (res) + str[i++] - '0';
		if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1))
			ft_error_manage(flag);
	}
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i ++;
	if (str[i])
		ft_error_manage(flag);
	return (sign * res);
}

int	bt_exit(char **cmd_vector, t_list *envp_list)
{	
	int	num;
	int	flag;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putstr_fd("exit\n", 2);
	(void)envp_list;
	flag = 0;
	if (check_word_cnt(cmd_vector) == 1)
		num = 0;
	else if (check_word_cnt(cmd_vector) == 2)
	{
		num = bt_atoi(cmd_vector[1], &flag);
		if (flag)
		{
			error_handler("exit", cmd_vector[1], NOT_NUM_ARG);
			exit (EX_OUTOF_RANGE);
		}
	}
	else
	{
		error_handler("exit", 0, MANY_ARG);
		return (EX_BT_FAIL);
	}
	exit ((unsigned char)num);
}
