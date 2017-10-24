/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/24 14:08:30 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

void	symtab_64(struct symtab_command *sc, char *ptr)
{
	DEBUG
	struct	nlist_64		*symbol_table;
	char					*stringtable;
	int						type;
	int						j;

	j = 0;
	symbol_table = (void *)ptr + sc->symoff;
	stringtable = (void *)ptr + sc->stroff;
	while (j < (int)sc->nsyms)
	{
		if (symbol_table[j].n_value)
			ft_putstr(ft_ptrf("%0*x ", symbol_table[j].n_value, 16));
		else
			printf("                 ");
		type = symbol_table[j].n_type & N_TYPE;
		if (type == N_UNDF || type == N_PBUD)
			ft_putstr(ft_ptrf("U  "));
		if (type == N_SECT)
			printf("T  ");
		printf("%s\n", stringtable + symbol_table[j].n_un.n_strx);
		j++;
	}
}

int		handle_64(char *title, char *ptr, int options)
{
	DEBUG
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	int						i;

	dprintf(1, "%s, %d\n", title, options);
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);

	i = 0;
	while (i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_64((struct symtab_command *)lc, ptr);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (0);

}
