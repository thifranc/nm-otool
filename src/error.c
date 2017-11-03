/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:05:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/03 10:05:45 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		handle_error(int flag)
{
	DEBUG
	dprintf(1, "err is %d\n", flag);
	return (1);
}

int		is_compromised(int size, int start, int jump, int offset)
{
	if (offset > size || jump - start > size)
		return (ERR_IS_COMPROMISED);
	else
		return (0);
}
