/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:23:12 by rchallie          #+#    #+#             */
/*   Updated: 2019/10/28 13:16:16 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //NOP

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
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (sub_char_str(s2, '\0', 0, len_str(s2) + 1));
	if (!s2)
		return (sub_char_str(s1, '\0', 0, len_str(s1) + 1));
	save_s1 = (char *)s1;
	s1_len = len_str(s1);
	s2_len = len_str(s2);
	if (!(new_str = malloc(sizeof(char) * (s1_len + s2_len + 1))))
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

//A virer et  mettre dans la boucle necessaire
char	*set_zero(char *s)
{
	while (*s)
		*s++ = '\0';
	return (s);
}

char	*get_content(char *line_get, int fd)
{
	size_t	line_end;
	char	*buffer;
	int		reader;

	line_end = 0;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	while ((reader = read(fd, buffer, BUFFER_SIZE) > 0))
	{
		buffer[BUFFER_SIZE] = '\0';
		line_get = join_str((const char *)line_get, (const char *)buffer);
		set_zero(buffer);
		while (line_get[line_end] && line_get[line_end] != '\n')
			line_end++;
		if (line_end != len_str(buffer) + 1 && line_get[line_end] == '\n')
			break ;
	}
	free(buffer);
	return (line_get);
}
