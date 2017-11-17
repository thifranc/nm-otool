/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:06:17 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/17 15:32:03 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/nm.h"

int		match_cpu(int archs, struct fat_arch *arch)
{
	int	i;

	i = 0;
	while (i < archs)
	{
		if (swap_bits(arch->cputype) == CPU_TYPE_X86_64)
			return (1);
		arch = (struct fat_arch *) ((void*)arch + sizeof(struct fat_arch) );
		i++;
	}
	return (0);
}

int		fat_arch(char *ptr, t_a g, int archs)
{
	struct fat_arch	*arch;
	int				i;
	int					matched;

	i = 0;
	//dprintf(1, "is 32 with %d archs\n", archs);
	arch = (struct fat_arch *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	matched = match_cpu(archs, arch);
	g.opt = matched ? g.opt & ~MANY_ARCHS : g.opt | MANY_ARCHS;
	while (i < archs)
	{
		if (!matched ||
				(matched && swap_bits(arch->cputype) == CPU_TYPE_X86_64))
			handle_macho((void *)ptr + swap_bits(arch->offset), g);
		arch = (struct fat_arch *) ((void*)arch + sizeof(struct fat_arch));
		i++;
	}
	return (0);
}

int		match_cpu_64(int archs, struct fat_arch_64 *arch)
{
	int	i;

	i = 0;
	while (i < archs)
	{
		if (swap_bits(arch->cputype) == CPU_TYPE_X86_64)
			return (1);
		arch = (struct fat_arch_64 *) ((void*)arch + sizeof(struct fat_arch_64) );
		i++;
	}
	return (0);
}

int		fat_arch_64(char *ptr, t_a g, int archs)
{
	struct fat_arch_64	*arch;
	int					i;
	int					matched;

	i = 0;
	//dprintf(1, "is 64 with %d archs\n", archs);
	arch = (struct fat_arch_64 *) ( (void*)ptr + sizeof(struct fat_header) ) ;
	matched = match_cpu_64(archs, arch);
	g.opt = matched ? g.opt & ~MANY_ARCHS : g.opt | MANY_ARCHS;
	while (i < archs)
	{
		if (!matched ||
				(matched && swap_bits(arch->cputype) == CPU_TYPE_X86_64))
			handle_macho((void *)ptr + swap_bits(arch->offset), g);
		handle_macho((void *)ptr + swap_bits(arch->offset), g);
		arch = (struct fat_arch_64 *) ((void*)arch + sizeof(struct fat_arch_64) );
		i++;
	}
	return (0);
}

int		handle_fat(char *ptr, t_a g)
{
	struct fat_header	*fat;
	int					i;

	i = 0;
	fat = (struct fat_header *)ptr;
	if (fat->magic == FAT_MAGIC_64 ||
		fat->magic == FAT_CIGAM_64)
	{
		fat_arch_64(ptr, g, swap_bits(fat->nfat_arch));
	}
	else
	{
		fat_arch(ptr, g, swap_bits(fat->nfat_arch));
	}
	return (0);
}
