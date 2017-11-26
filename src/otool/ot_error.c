/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:05:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/26 16:42:39 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

int						handle_error(int flag, char *filename)
{
	char	*error;
	char	*msg;

	if (flag == ERR_MAGIC)
		error = "The file was not recognized as a valid object file";
	if (flag == ERR_OPEN)
		error = "Error while opening, see perror or strerror";
	if (flag == ERR_FSTAT)
		error = "Error on fstat";
	if (flag == ERR_MMAP || flag == ERR_MALLOC)
		error = "No memory available left";
	if (flag == ERR_IS_COMPROMISED)
		error = "File seems to be compromised";
	if (flag & ERR_MULTI_OPT)
		error = "may only occur zero or one times!";
	msg = ft_ptrf("ft_nm: %s: %s\n%s",
			filename, error, flag == ERR_MAGIC ? "\n" : "");
	ft_putstr_fd(msg, 1);
	free(msg);
	msg = NULL;
	return (1);
}

int						is_compromised(long size,
		long start, long jump, long offset)
{
	if (offset > size || jump - start > size)
		return (ERR_IS_COMPROMISED);
	else
		return (0);
}

long long unsigned		swaptest(long long int a, char options)
{
	if (options & TO_SWAP)
		return (swap_bits(a));
	else
		return (a);
}

void					free_tab(char ***tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if ((*tab)[i][0])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}
