/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:20:38 by rchallie          #+#    #+#             */
/*   Updated: 2019/10/31 13:40:31 by rchallie         ###   ########.fr       */
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

char	*get_content(char *line_get, int fd)
{
	size_t	line_end;
	char	*buffer;
	int		reader;

	line_end = 0;
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (0);
	reader = 1;
	while (reader > 0)
	{
		init_buffer(buffer);
		reader = read(fd, buffer, BUFFER_SIZE);
		line_get = join_str((const char *)line_get, (const char *)buffer);
		while (line_get[line_end] && line_get[line_end] != '\n')
			line_end++;
		if (line_end != len_str(buffer) + 1 && line_get[line_end] == '\n')
			break ;
	}
	init_buffer(buffer);
	if (!line_get)
		return (0);
	free(buffer);
	return (line_get);
}
