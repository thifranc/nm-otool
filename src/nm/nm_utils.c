/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 12:46:07 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/28 19:48:22 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"

char	*get_cpu_string(int cputype)
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

void	print_tab(char **tab, struct s_a g)
{
	int		i;
	int		jump;
	char	*title;

	i = 0;
	jump = g.opt & IS_32 ? 11 : 19;
	title = ft_ptrf("");
	if (g.opt & MANY_ARGS && !(g.opt & IS_FAT))
		title = ft_ptrf("\n%s:\n", g.title);
	else if (g.opt & NO_X86_64)
	{
		title = ft_ptrf("\n%s (for architecture %s):\n", g.title, g.cputype);
		if (!(g.opt & MANY_ARCHS))
			title = ft_ptrf("%s:\n", g.title);
	}
	ft_putstrdel(title);
	while (i < g.nsyms)
	{
		if (!(g.opt & OPT_U) || (g.opt & OPT_U &&
				(tab[i][jump - 2] == 'U' || tab[i][jump - 2] == 'u')))
			ft_putstr(g.opt & OPT_J ? tab[i] + jump : tab[i]);
		i++;
	}
}

void	utils_match_nsect(char *segname,
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

void	init_g_struct(t_a *g)
{
	g->data_sec = 0;
	g->bss_sec = 0;
	g->text_sec = 0;
	g->n_sect = 0;
}

char	get_type(int type, t_a g, int fallback)
{
	if (type == N_SECT)
	{
		type = fallback;
		if (type == g.bss_sec)
			return ('B');
		else if (type == g.data_sec)
			return ('D');
		else if (type == g.text_sec)
			return ('T');
		else
			return ('S');
	}
	else
	{
		if (type == N_UNDF || type == N_PBUD)
			return ('U');
		if (type == N_ABS)
			return ('A');
		if (type == N_INDR)
			return ('I');
	}
	return (' ');
}
