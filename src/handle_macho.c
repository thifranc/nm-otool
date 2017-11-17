/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_macho.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 14:48:06 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 15:29:57 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char	macho_config(char *ptr, unsigned int *options)
{
	//DEBUG
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number != MH_CIGAM_64 &&
			magic_number != MH_CIGAM &&
			magic_number != MH_MAGIC &&
			magic_number != MH_MAGIC_64)
		return (ERR_MAGIC);
	if (magic_number == MH_CIGAM_64 || magic_number == MH_CIGAM)
	{
		*options = *options | TO_SWAP;
	}
	else
		*options = *options & ~TO_SWAP;
	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		*options = *options | IS_32;
	else
		*options = *options & ~IS_32;
	return (0);
}

int		handle_macho(char *ptr, t_a g)
{
	//DEBUG
	int		error_code;

	if ((error_code = macho_config(ptr, &(g.opt))) != 0)
		handle_error(error_code);

	//printBits(sizeof(g.opt), &(g.opt));
	if (g.opt & IS_32)
		handle_32(ptr, g);
	else
		handle_64(ptr, g);
	return (0);
}
