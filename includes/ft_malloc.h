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

typedef struct		s_link {
	struct s_link	*end;
	struct s_link	*next;
}					t_link;


#endif 
