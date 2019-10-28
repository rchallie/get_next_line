/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:20:38 by rchallie          #+#    #+#             */
/*   Updated: 2019/10/28 13:36:52 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>              //NOP
#include <fcntl.h>              //NOPy


char	*set_line(char **line, char *line_get)
{
	size_t		line_end;

	line_end = 0;
	while (line_get[line_end] && line_get[line_end] != '\n')
		line_end++;
	*line = sub_char_str(line_get, '\n', 0, len_str(line_get));
	free(line_get);
	if (*line)
		line_get = sub_char_str(line_get, '\0', (int)line_end + 1,
		len_str(line_get) - (line_end + 1));
	else
	{
		*line = sub_char_str(line_get, '\0', 0, len_str(line_get));
		line_get = NULL;
		return (0);
	}
	return (line_get);
}

//free 
int		get_next_line(int fd, char **line)
{
	size_t		line_end;
	static char	*line_get;

	if (!line)
		return (-1);
	line_get = get_content(line_get, fd);
	if (!line_get)
		return (-1);
	line_end = 0;
	if (line_get)
	{
		line_get = set_line(line, line_get);
		if (line_get == 0)
			return (0);
		free(*line);
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

int main()
{
	int     fd;
	char	**line;
	int		rtn;

	line = malloc(sizeof(char *) * 2);
	if (!line)
		return (0);
	write(1,"test1\n", 6);
	rtn = 1;
	fd = open("tests/text.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (text) : \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("res is %d output : |%s|\n", rtn, *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);

	while(1) {}
	/*write(1,"test2\n", 6);
	rtn = 1;
	fd = open("tests/eight.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (eight): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	write(1,"test3\n", 6);
	rtn = 1;
	fd = open("tests/empty.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (empty): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/file001.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (file001): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/file002.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (file002): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/file003.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (file003): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/many_big_lines.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (many_big_lines): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/many_nl.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (many_nl): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/no_nl.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (no_nl): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/one_char.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (one_char): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	close(fd);
	rtn = 1;
	fd = open("tests/only_nl.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (only_nl): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
			close(fd);
	rtn = 1;
	fd = open("tests/two_big_lines.txt",O_RDONLY, 1);
	if (fd)
	{
		printf("Lecture du fichier (two_big_lines): \n");
		while (rtn == 1)
		{
			rtn = get_next_line(fd, line);
			printf("|%s|\n", *line);
		}
	}
	else
		printf("No FD.\n");
	return (0);*/
}