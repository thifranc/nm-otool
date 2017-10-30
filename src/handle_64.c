/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:41:38 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/30 16:29:26 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		symtab_64(struct symtab_command *sc, char *ptr, char ***all_string)
{
	DEBUG
	struct	nlist_64	*symbol_table;
	char				*stringtable;
	int					type;
	int					j;

	if (!(*all_string = (char**)malloc(sizeof(char *) * sc->nsyms)))
		return (ERR_MALLOC);

	symbol_table = (void *)ptr + sc->symoff;
	stringtable = (void *)ptr + sc->stroff;

	j = 0;
	while (j < (int)sc->nsyms)
	{
		
		if (!((*all_string)[j] = (char*)malloc(sizeof(char)
			* (19 + ft_strlen(stringtable + symbol_table[j].n_un.n_strx)))))
			return (ERR_MALLOC);
		type = symbol_table[j].n_type & N_TYPE;

		(*all_string)[j] = ft_ptrf("%s %s %s\n",
			symbol_table[j].n_value ?
				ft_ptrf("%0*x", symbol_table[j].n_value, 16) :
				"                ",
			get_type(type), stringtable + symbol_table[j].n_un.n_strx);
		j++;
	}
	j = 0;
	while (j < (int)sc->nsyms)
	{
		dprintf(1, "%s", (*all_string)[j]);
		j++;
	}
	return (0);
}

int		handle_64(char *title, char *ptr, t_a g)
{
	DEBUG
	struct	mach_header_64	*header;
	struct	load_command	*lc;
	int						i;
	char					**output;

	dprintf(1, "%s, %d\n", title, g.opt);
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(struct mach_header_64);

	i = 0;
	while (i < (int)header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab_64((struct symtab_command *)lc, ptr, &output);
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return (0);

}
