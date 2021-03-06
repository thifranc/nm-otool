/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 17:06:17 by thifranc          #+#    #+#             */
/*   Updated: 2017/11/30 15:26:29 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		match_cpu(int archs, struct fat_arch *arch)
{
	int	i;

	i = 0;
	while (i < archs)
	{
		if (swap_bits(arch->cputype) == CPU_TYPE_X86_64)
			return (1);
		arch = (struct fat_arch *)((void*)arch + sizeof(struct fat_arch));
		i++;
	}
	return (0);
}

int		fat_arch(char *ptr, t_a *g, int archs)
{
	struct fat_arch	*arch;
	int				i;
	int				used;
	int				matched;
	int				error_code;

	i = 0;
	used = 0;
	arch = (struct fat_arch *)((void*)ptr + sizeof(struct fat_header));
	matched = match_cpu(archs, arch);
	g->opt = matched ? g->opt & ~NO_X86_64 : g->opt | NO_X86_64;
	while (i < archs)
	{
		g->cputype = get_cpu_string(swap_bits(arch->cputype));
		if (!matched ||
	(matched && swap_bits(arch->cputype) == CPU_TYPE_X86_64 && !used++))
		{
			if ((error_code =
				handle_macho((void *)ptr + swap_bits(arch->offset), g)) != 0)
				return (error_code);
		}
		arch = (struct fat_arch *)((void*)arch + sizeof(struct fat_arch));
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
		arch = (struct fat_arch_64 *)((void*)arch + sizeof(struct fat_arch_64));
		i++;
	}
	return (0);
}

int		fat_arch_64(char *ptr, t_a *g, int archs)
{
	struct fat_arch_64	*arch;
	int					i;
	int					used;
	int					matched;
	int					error_code;

	i = 0;
	used = 0;
	arch = (struct fat_arch_64 *)((void*)ptr + sizeof(struct fat_header));
	matched = match_cpu_64(archs, arch);
	g->opt = matched ? g->opt & ~NO_X86_64 : g->opt | NO_X86_64;
	while (i < archs)
	{
		g->cputype = get_cpu_string(swap_bits(arch->cputype));
		if (!matched ||
		(matched && swap_bits(arch->cputype) == CPU_TYPE_X86_64 && !used++))
		{
			if ((error_code =
				handle_macho((void *)ptr + swap_bits(arch->offset), g)) != 0)
				return (error_code);
		}
		arch = (struct fat_arch_64 *)((void*)arch + sizeof(struct fat_arch_64));
		i++;
	}
	return (0);
}

int		handle_fat(char *ptr, t_a *g)
{
	struct fat_header	*fat;
	int					error_code;

	error_code = 0;
	fat = (struct fat_header *)ptr;
	g->opt = swap_bits(fat->nfat_arch) > 1 ?
		g->opt | MANY_ARCHS :
		g->opt & ~MANY_ARCHS;
	if (fat->magic == FAT_MAGIC_64 ||
		fat->magic == FAT_CIGAM_64)
	{
		error_code = fat_arch_64(ptr, g, swap_bits(fat->nfat_arch));
	}
	else
	{
		error_code = fat_arch(ptr, g, swap_bits(fat->nfat_arch));
	}
	return (error_code);
}
