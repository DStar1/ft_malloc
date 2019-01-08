#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stdio.h>
# include "libft.h"
# include <sys/mman.h>
# include <errno.h>


# define SMALL_PAGE_SIZE 8
# define SMALL_SIZE (8 * 4096)
# define MED_PAGE_SIZE 32
# define MED_SIZE (32 * 4096)

/*
** Old way, less efficient
*/
typedef struct		s_link {
	struct s_link	*end;
	struct s_link	*next;
}					t_link;

typedef struct		s_allocated {
	t_link			*small;
	size_t			small_max;
	t_link			*med;
	size_t			med_max;
	t_link			*large;
}					t_allocated;

/*
** Trying different way, more efficient
*/
typedef struct		s_block {
	char			end;
	char			allocated;
	int				size;
	struct s_block	*next;
}					t_block;

typedef struct		s_pages {
	t_block			*small;
	t_block			*med;
	t_block			*large;
}					t_pages;

void				*ft_malloc(size_t size);
// static void			*add_small_link(t_link *start, long size, long max);
t_allocated			*allocated_data();

#endif 
