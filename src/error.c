/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 15:05:56 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/24 13:53:44 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

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
	ft_putstr_fd(msg, 2);
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

int						handle_lc(struct load_command lc_clean,
		struct load_command *lc, t_a *g, char *ptr)
{
	int	error_code;

	if (lc_clean.cmd == (g->opt & IS_32 ? LC_SEGMENT : LC_SEGMENT_64))
		g->opt & IS_32 ?
			get_n_sect32((struct segment_command *)lc, g) :
			get_n_sect64((struct segment_command_64 *)lc, g);
	if (lc_clean.cmd == LC_SYMTAB)
	{
		error_code = g->opt & IS_32 ?
			symtab_32(swap_sc((struct symtab_command *)lc, g->opt), ptr, g) :
			symtab_64(swap_sc((struct symtab_command *)lc, g->opt), ptr, g);
		if (error_code != 0)
			return (error_code);
	}
	return (0);
}

long long unsigned		swaptest(long long int a, char options)
{
	if (options & TO_SWAP)
		return (swap_bits(a));
	else
		return (a);
}
