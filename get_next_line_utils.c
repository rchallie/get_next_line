/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:23:12 by rchallie          #+#    #+#             */
/*   Updated: 2019/10/28 17:48:23 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	len_str(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (0);
	if (!*s)
		return (0);
	while (*s++)
		len++;
	return (len);
}

char	*sub_char_str(const char *s, int c, int start, size_t max_len)
{
	size_t		i;
	size_t		j;
	char		*new_str;

	i = 0;
	j = -1;
	while (s[i + start] && s[i + start] != c && i < max_len)
		i++;
	if (s[i + start] == '\0' && c != '\0')
		return (0);
	if (!(new_str = malloc(sizeof(char) * (i + 1))))
		return (0);
	while (++j < i)
		new_str[j] = s[start + j];
	new_str[i] = '\0';
	return (new_str);
}

char	*join_str(const char *s1, const char *s2)
{
	char	*new_str;
	char	*save_nstr;
	char	*save_s1;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (sub_char_str(s2, '\0', 0, len_str(s2) + 1));
	if (!s2)
		return (sub_char_str(s1, '\0', 0, len_str(s1) + 1));
	save_s1 = (char *)s1;
	if (!(new_str = malloc(sizeof(char) * (len_str(s1) + len_str(s2) + 1))))
		return (0);
	save_nstr = new_str;
	while (*s1)
		*new_str++ = *s1++;
	while (*s2)
		*new_str++ = *s2++;
	*new_str = '\0';
	new_str = save_nstr;
	free((void *)save_s1);
	return (new_str);
}

char	*set_line(char **line, char *line_get)
{
	size_t		line_end;
	char		*save_line_get;

	line_end = 0;
	save_line_get = line_get;
	while (line_get[line_end] && line_get[line_end] != '\n')
		line_end++;
	*line = sub_char_str(line_get, '\n', 0, len_str(line_get));
	if (*line)
		line_get = sub_char_str(line_get, '\0', (int)line_end + 1,
		len_str(line_get) - (line_end + 1));
	else
	{
		*line = sub_char_str(line_get, '\0', 0, len_str(line_get));
		free(save_line_get);
		return (0);
	}
	free(save_line_get);
	return (line_get);
}

char	*get_content(char *line_get, int fd)
{
	size_t	line_end;
	char	*buffer;
	char	*save_buff;
	int		reader;

	line_end = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	save_buff = buffer;
	while ((reader = read(fd, buffer, BUFFER_SIZE) > 0))
	{
		buffer[BUFFER_SIZE] = '\0';
		line_get = join_str((const char *)line_get, (const char *)buffer);
		while (*buffer)
			*buffer++ = '\0';
		while (line_get[line_end] && line_get[line_end] != '\n')
			line_end++;
		if (line_end != len_str(buffer) + 1 && line_get[line_end] == '\n')
			break ;
	}
	if (!line_get)
		return (0);
	free(save_buff);
	return (line_get);
}
