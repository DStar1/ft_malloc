#include "ft_malloc.h"


/*
** allocate using mmap
*/

t_allocated *data = NULL;
t_allocated		*allocated_data()
{
	if (!data)
	{
		data = mmap(NULL, sizeof(t_allocated) + getpagesize() * 100 * SMALL_PAGE_SIZE
					+ getpagesize() * 100 * MED_PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		data->small_max = getpagesize() * 100 * SMALL_PAGE_SIZE;
		data->small = (t_link*)(data + 1);
		data->small->end = data->small + 2;
		data->small->next = NULL;
		data->med_max = getpagesize() * 100 * MED_PAGE_SIZE;
		data->med = (t_link*)(data + 1);
		data->med->end = data->med + 1;
		data->med->next = NULL;
		data->large = (t_link*)(data + 1);
		data->large->end = data->large + 1;
		data->large->next = NULL;
	}
	return (data);
}

////////////// Just seeing if this function works //////////
static void	*small_med_link(t_link *start, long size, long max)
{
	t_link *node;
	t_link *tmp;

	node = start;
	while (node->next)
	{
		if ((char*)node->next - (char*)node->end >= size)
			break ;
		node = node->next;
	}
	if ((char*)node->end + size > (char*)start + max)
	{
		errno = ENOMEM;
		return (NULL);
	}
	tmp = node->next;
	node->next = node->end;
	node->next->end = (t_link*)((char*)node->next + size);
	node->next->next = tmp;
	return (node->next + 1);
}

/*
** (IDEA for malloc() function)
*/

void	*ft_malloc(size_t size)
{
	t_link *node;

	size += sizeof(t_link);
	if (size <= SMALL_SIZE)
		return(small_med_link(allocated_data()->small, size, allocated_data()->small_max));
	if (size <= MED_SIZE)
		return(small_med_link(allocated_data()->med, size, allocated_data()->med_max));
	node = allocated_data()->large;
	//iterate though node to get to NULL
	while (node->next)
	{
		node = node->next;
	}
	node->next = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (node->next == NULL) {errno = ENOMEM; return(NULL);}
	node->next->end = (t_link*)((char*)node->next + size);
	node->next->next = NULL;
	return (node->next+1);	
}

