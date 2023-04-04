/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbritani <sbritani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:29:05 by sbritani          #+#    #+#             */
/*   Updated: 2022/12/21 21:10:41 by sbritani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_connect(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*remains(char *res)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (res[i] && res[i] != '\n')
		i++;
	if (!res[i])
	{
		free(res);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(res) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (res[i])
		line[j++] = res[i++];
	free(res);
	return (line);
}

char	*make_res(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	j = i;
	i = -1;
	while (++i < j)
		line[i] = buffer[i];
	if (buffer[i])
		line[i++] = '\n';
	return (line);
}

char	*fill_buffer(int fd, char *res)
{
	char	*buffer;
	int		read_count;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	read_count = 1;
	while (read_count > 0)
	{
		read_count = read(fd, buffer, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_count] = 0;
		res = free_connect(res, buffer);
		if (ft_str_chr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res[MAXFDS];
	char		*output;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	res[fd] = fill_buffer(fd, res[fd]);
	if (!res[fd])
		return (NULL);
	output = make_res(res[fd]);
	res[fd] = remains(res[fd]);
	return (output);
}
