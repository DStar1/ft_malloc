#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include "libft.h"
# include <sys/mman.h>
# include <errno.h>

# define SMALL_PAGE_SIZE 8
# define SMALL_SIZE (SMALL_PAGE_SIZE * 4096)
# define MED_PAGE_SIZE 32
# define MED_SIZE (MED_PAGE_SIZE * 4096)

/*
** Trying different way, more efficient
*/
#define ALIGNMENT 16
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~(ALIGNMENT-1))
#define CHUNK_SIZE (4 * 4096)
#define CHUNK_ALIGN(size) (((size)+(CHUNK_SIZE-1)) & ~(CHUNK_SIZE-1))

#define OVERHEAD sizeof(block_header)
#define HDRP(bp) ((char *)(bp) - sizeof(block_header))
#define GET_SIZE(p) ((block_header *)(p))->size
#define GET_ALLOC(p) ((block_header *)(p))->allocated
#define GET_END(p) ((block_header *)(p))->end
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))
#define NEXT_PG(bp) ((t_page *)(bp - (sizeof(t_page) + OVERHEAD + 1)))->next ///make sure (-sizeof(t_page)) is correct
#define END_PG(bp) ((t_page *)(bp - (sizeof(t_page) + OVERHEAD + 1)))->end ///make sure (-sizeof(t_page)) is correct

typedef struct {
	size_t size;
	char allocated;
	char end;
} block_header;

typedef struct s_page {
	struct s_page	*next;
	struct s_page	*end;
} t_page;

typedef struct		s_pages {
	t_page			*small;
	size_t			small_max;
	t_page			*med;
	size_t			med_max;
	t_page			*large;
}					t_pages;

// typedef struct {
//  size_t size;
//  char allocated;
// } block_header;

// typedef struct		s_block {
// 	char			end;
// 	char			allocated;
// 	int				size;
// 	struct s_block	*next;
// }					t_block;

// typedef struct		s_pages {
// 	t_block			*small;
// 	t_block			*med;
// 	t_block			*large;
// }					t_pages;

// /*
// ** Old way, less efficient
// */
// typedef struct		s_link {
// 	struct s_link	*end;
// 	struct s_link	*next;
// }					t_link;

// typedef struct		s_allocated {
// 	t_link			*small;
// 	size_t			small_max;
// 	t_link			*med;
// 	size_t			med_max;
// 	t_link			*large;
// }					t_allocated;



// void				*mm_malloc(size_t size);
// // static void			*add_small_link(t_link *start, long size, long max);
// t_allocated			*allocated_data();

// void set_allocated(void *bp, size_t size);
// void extend(size_t new_size);
// int mm_init();
t_pages		*allocated_data();
void *ft_malloc(size_t size);
int ft_free(void *ptr);


#endif 
