/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 18:48:16 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

char					*get_cpu_string(int cputype)
{
	char	*ret;

	ret = "";
	ret = cputype == CPU_TYPE_VAX ? "vax" : ret;
	ret = cputype == CPU_TYPE_MC680x0 ? "mc680x0" : ret;
	ret = cputype == CPU_TYPE_X86 ? "x86" : ret;
	ret = cputype == CPU_TYPE_I386 ? "i386" : ret;
	ret = cputype == CPU_TYPE_X86_64 ? "x86_64" : ret;
	ret = cputype == CPU_TYPE_MC98000 ? "mc98000" : ret;
	ret = cputype == CPU_TYPE_HPPA ? "hppa" : ret;
	ret = cputype == CPU_TYPE_ARM ? "arm" : ret;
	ret = cputype == CPU_TYPE_ARM64 ? "arm64" : ret;
	ret = cputype == CPU_TYPE_MC88000 ? "mc88000" : ret;
	ret = cputype == CPU_TYPE_SPARC ? "sparc" : ret;
	ret = cputype == CPU_TYPE_I860 ? "i860" : ret;
	ret = cputype == CPU_TYPE_POWERPC ? "ppc" : ret;
	ret = cputype == CPU_TYPE_POWERPC64 ? "ppc64" : ret;
	return (ret);
}

void					print_tab(char **tab, struct s_a g)
{
	int		i;
	char	*title;

	i = 0;
	title = "";
	if (g.opt & MANY_ARGS && !(g.opt & IS_FAT))
		title = ft_ptrf("\n%s:\n", g.title);
	if (g.opt & NO_X86_64)
		title = ft_ptrf("\n%s (for architecture %s):\n", g.title, g.cputype);
	if (g.opt & IS_FAT && g.opt & NO_X86_64 && !(g.opt & MANY_ARCHS))
		title = ft_ptrf("%s:\n", g.title);
	ft_putstr(title);
	while (i < g.nsyms)
	{
		ft_putstr(tab[i]);
		i++;
	}
}

void					utils_match_nsect(char *segname,
		char *sectname, t_a *g, int cur)
{
	if (ft_strcmpi(segname, sectname) == 0)
	{
		if (!ft_strcmp(sectname, "__data"))
			g->data_sec = g->n_sect + cur + 1;
		else if (!ft_strcmp(sectname, "__text"))
			g->text_sec = g->n_sect + cur + 1;
	}
	else if (!ft_strcmp(segname, "__DATA") && !ft_strcmp(sectname, "__bss"))
		g->bss_sec = g->n_sect + cur + 1;
}

long long unsigned		swap_bits(long long int num)
{
	return (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) |
			((num >> 8) & 0xff00) |
			((num << 24) & 0xff000000));
}

long long unsigned		swaptest(long long int a, char options)
{
	if (options & TO_SWAP)
		return (swap_bits(a));
	else
		return (a);
}
