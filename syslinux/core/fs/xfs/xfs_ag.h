/*
 * Taken from Linux kernel tree (linux/fs/xfs)
 *
 * Copyright (c) 2000-2003,2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * Copyright (c) 2012 Paulo Alcantara <pcacjr@zytor.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef XFS_AG_H_
#define	XFS_AG_H_

#include "xfs_types.h"

/*
 * Allocation group header
 * This is divided into three structures, placed in sequential 512-byte
 * buffers after a copy of the superblock (also in a 512-byte buffer).
 */

typedef uint32_t xfs_agino_t;

struct xfs_buf;
struct xfs_mount;
struct xfs_trans;

#define	XFS_AGF_MAGIC	"XAGF"
#define	XFS_AGF_VERSION	1
#define	XFS_AGI_VERSION	1

#define	XFS_AGF_GOOD_VERSION(v)	((v) == XFS_AGF_VERSION)
#define	XFS_AGI_GOOD_VERSION(v)	((v) == XFS_AGI_VERSION)

/*
 * Btree number 0 is bno, 1 is cnt.  This value gives the size of the
 * arrays below.
 */
#define	XFS_BTNUM_AGF	((int)XFS_BTNUM_CNTi + 1)

/*
 * The second word of agf_levels in the first a.g. overlaps the EFS
 * superblock's magic number.  Since the magic numbers valid for EFS
 * are > 64k, our value cannot be confused for an EFS superblock's.
 */

typedef struct xfs_agf {
	/*
	 * Common allocation group header information
	 */
	uint32_t		agf_magicnum;	/* magic number == XFS_AGF_MAGIC */
	uint32_t		agf_versionnum;	/* header version == XFS_AGF_VERSION */
	uint32_t		agf_seqno;	/* sequence # starting from 0 */
	uint32_t		agf_length;	/* size in blocks of a.g. */
	/*
	 * Freespace information
	 */
	uint32_t		agf_roots[XFS_BTNUM_AGF];	/* root blocks */
	uint32_t		agf_spare0;	/* spare field */
	uint32_t		agf_levels[XFS_BTNUM_AGF];	/* btree levels */
	uint32_t		agf_spare1;	/* spare field */
	uint32_t		agf_flfirst;	/* first freelist block's index */
	uint32_t		agf_fllast;	/* last freelist block's index */
	uint32_t		agf_flcount;	/* count of blocks in freelist */
	uint32_t		agf_freeblks;	/* total free blocks */
	uint32_t		agf_longest;	/* longest free space */
	uint32_t		agf_btreeblks;	/* # of blocks held in AGF btrees */
} xfs_agf_t;

#define	XFS_AGF_MAGICNUM	0x00000001
#define	XFS_AGF_VERSIONNUM	0x00000002
#define	XFS_AGF_SEQNO		0x00000004
#define	XFS_AGF_LENGTH		0x00000008
#define	XFS_AGF_ROOTS		0x00000010
#define	XFS_AGF_LEVELS		0x00000020
#define	XFS_AGF_FLFIRST		0x00000040
#define	XFS_AGF_FLLAST		0x00000080
#define	XFS_AGF_FLCOUNT		0x00000100
#define	XFS_AGF_FREEBLKS	0x00000200
#define	XFS_AGF_LONGEST		0x00000400
#define	XFS_AGF_BTREEBLKS	0x00000800
#define	XFS_AGF_NUM_BITS	12
#define	XFS_AGF_ALL_BITS	((1 << XFS_AGF_NUM_BITS) - 1)

#define XFS_AGF_FLAGS \
	{ XFS_AGF_MAGICNUM,	"MAGICNUM" }, \
	{ XFS_AGF_VERSIONNUM,	"VERSIONNUM" }, \
	{ XFS_AGF_SEQNO,	"SEQNO" }, \
	{ XFS_AGF_LENGTH,	"LENGTH" }, \
	{ XFS_AGF_ROOTS,	"ROOTS" }, \
	{ XFS_AGF_LEVELS,	"LEVELS" }, \
	{ XFS_AGF_FLFIRST,	"FLFIRST" }, \
	{ XFS_AGF_FLLAST,	"FLLAST" }, \
	{ XFS_AGF_FLCOUNT,	"FLCOUNT" }, \
	{ XFS_AGF_FREEBLKS,	"FREEBLKS" }, \
	{ XFS_AGF_LONGEST,	"LONGEST" }, \
	{ XFS_AGF_BTREEBLKS,	"BTREEBLKS" }

/* disk block (xfs_daddr_t) in the AG */
#define XFS_AGF_DADDR(mp)	((xfs_daddr_t)(1 << (mp)->m_sectbb_log))
#define	XFS_AGF_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGF_DADDR(mp))
#define	XFS_BUF_TO_AGF(bp)	((xfs_agf_t *)((bp)->b_addr))

extern int xfs_read_agf(struct xfs_mount *mp, struct xfs_trans *tp,
			xfs_agnumber_t agno, int flags, struct xfs_buf **bpp);

/*
 * Size of the unlinked inode hash table in the agi.
 */
#define	XFS_AGI_UNLINKED_BUCKETS	64

#define	XFS_AGI_MAGICNUM	0x00000001
#define	XFS_AGI_VERSIONNUM	0x00000002
#define	XFS_AGI_SEQNO		0x00000004
#define	XFS_AGI_LENGTH		0x00000008
#define	XFS_AGI_COUNT		0x00000010
#define	XFS_AGI_ROOT		0x00000020
#define	XFS_AGI_LEVEL		0x00000040
#define	XFS_AGI_FREECOUNT	0x00000080
#define	XFS_AGI_NEWINO		0x00000100
#define	XFS_AGI_DIRINO		0x00000200
#define	XFS_AGI_UNLINKED	0x00000400
#define	XFS_AGI_NUM_BITS	11
#define	XFS_AGI_ALL_BITS	((1 << XFS_AGI_NUM_BITS) - 1)

/* disk block (xfs_daddr_t) in the AG */
#define XFS_AGI_DADDR(mp)	((xfs_daddr_t)(2 << (mp)->m_sectbb_log))
#define	XFS_AGI_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGI_DADDR(mp))
#define	XFS_BUF_TO_AGI(bp)	((xfs_agi_t *)((bp)->b_addr))

extern int xfs_read_agi(struct xfs_mount *mp, struct xfs_trans *tp,
				xfs_agnumber_t agno, struct xfs_buf **bpp);

/*
 * The third a.g. block contains the a.g. freelist, an array
 * of block pointers to blocks owned by the allocation btree code.
 */
#define XFS_AGFL_DADDR(mp)	((xfs_daddr_t)(3 << (mp)->m_sectbb_log))
#define	XFS_AGFL_BLOCK(mp)	XFS_HDR_BLOCK(mp, XFS_AGFL_DADDR(mp))
#define XFS_AGFL_SIZE(mp)	((mp)->m_sb.sb_sectsize / sizeof(xfs_agblock_t))
#define	XFS_BUF_TO_AGFL(bp)	((xfs_agfl_t *)((bp)->b_addr))

typedef struct xfs_agfl {
	uint32_t		agfl_bno[1];	/* actually XFS_AGFL_SIZE(mp) */
} xfs_agfl_t;

/*
 * tags for inode radix tree
 */
#define XFS_ICI_NO_TAG		(-1)	/* special flag for an untagged lookup
					   in xfs_inode_ag_iterator */
#define XFS_ICI_RECLAIM_TAG	0	/* inode is to be reclaimed */

#define	XFS_AG_MAXLEVELS(mp)		((mp)->m_ag_maxlevels)
#define	XFS_MIN_FREELIST_RAW(bl,cl,mp)	\
	(MIN(bl + 1, XFS_AG_MAXLEVELS(mp)) + MIN(cl + 1, XFS_AG_MAXLEVELS(mp)))
#define	XFS_MIN_FREELIST(a,mp)		\
	(XFS_MIN_FREELIST_RAW(		\
		be32_to_cpu((a)->agf_levels[XFS_BTNUM_BNOi]), \
		be32_to_cpu((a)->agf_levels[XFS_BTNUM_CNTi]), mp))
#define	XFS_MIN_FREELIST_PAG(pag,mp)	\
	(XFS_MIN_FREELIST_RAW(		\
		(unsigned int)(pag)->pagf_levels[XFS_BTNUM_BNOi], \
		(unsigned int)(pag)->pagf_levels[XFS_BTNUM_CNTi], mp))

/*
 * For checking for bad ranges of xfs_daddr_t's, covering multiple
 * allocation groups or a single xfs_daddr_t that's a superblock copy.
 */
#define	XFS_AG_CHECK_DADDR(mp,d,len)	\
	((len) == 1 ? \
	    ASSERT((d) == XFS_SB_DADDR || \
		   xfs_daddr_to_agbno(mp, d) != XFS_SB_DADDR) : \
	    ASSERT(xfs_daddr_to_agno(mp, d) == \
		   xfs_daddr_to_agno(mp, (d) + (len) - 1)))

#endif	/* XFS_AG_H_ */
