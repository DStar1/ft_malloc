#include "ft_malloc.h"


/*
** (IDEA for alloc_small_med() function)
** allocate using mmap and then create new link
** 
** 
** 
*/

// static void		*alloc_small_med(t_link *start, long size, long max)
// {

// }

/*
** (IDEA for malloc() function)
** t_link *node
** if size <= SMALL_SIZE {ret(alloc(small))}
** if size <= MED_SIZE {ret(alloc(med))}
** node = aloc(large)
** iterate though node to get to NULL
** node->next = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
** if this node == NULL {errno = ENOMEM; return(NULL)}
** node->next->end = add size
** node->next->next = NULL
** ret(node->next+1)
*/

// void	malloc(size_t size)
// {

// }

int		main(int argc, char *argv[])
{
	ft_printf("Project %s successfully created! \n", argv[0]);
	return (argc);
}
