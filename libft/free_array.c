/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 17:07:02 by hasmith           #+#    #+#             */
/*   Updated: 2017/11/18 15:40:51 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != '\0')
	{
		free(array[i]);
		i++;
	}
	free(array);
}
