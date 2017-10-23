/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thifranc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 18:48:32 by thifranc          #+#    #+#             */
/*   Updated: 2017/10/23 17:27:56 by thifranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

#define ERR_MULTI_OPT 128
#define ERR_OPEN 1
#define ERR_FSTAT 2
#define ERR_MMAP 4
#define ERR_MAGIC 8

#define OPT_R 1
#define OPT_P 2
#define OPT_N 4
#define OPT_U 8
#define OPT_J 16
#define TO_SWAP 32
#define IS_32 64

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <ar.h>

int		parser(int ac, char **av);
void	printBits(size_t const size, void const * const ptr);
int		error(int flag);

#endif
