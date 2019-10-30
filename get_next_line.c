/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:20:38 by rchallie          #+#    #+#             */
/*   Updated: 2019/10/30 14:40:00 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	size_t		line_end;
	static char	*line_get;

	if (!line || fd < 0)
		return (-1);
	line_get = get_content(line_get, fd);
	line_end = 0;
	if (line_get)
	{
		line_get = set_line(line, line_get);
		if (line_get == 0)
			return (0);
	}
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (-1);
		*line[0] = '\0';
		return (0);
	}
	return (1);
}
