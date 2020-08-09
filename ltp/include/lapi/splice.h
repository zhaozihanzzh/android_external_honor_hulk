/*
 * Copyright (c) International Business Machines  Corp., 2007
 * Copyright (c) 2014 Fujitsu Ltd.
 *
 * This program is free software;  you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#ifndef SPLICE_H
#define SPLICE_H

#include "config.h"
#include "lapi/syscalls.h"

#if !defined(HAVE_SPLICE)
ssize_t splice(int fd_in, loff_t *off_in, int fd_out,
	loff_t *off_out, size_t len, unsigned int flags)
{
	return tst_syscall(__NR_splice, fd_in, off_in,
		fd_out, off_out, len, flags);
}
#endif

#endif /* SPLICE_H */
