/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:06:03 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/22 13:48:59 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*strdup_to_newline(char *str)
{
	size_t	i;
	char	*n_str;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	n_str = malloc(i + 1);
	if (!n_str)
		return (NULL);
	n_str[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		n_str[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		n_str[i] = '\n';
	return (n_str);
}

char	*read_chunks(int fd, char *buf, char *str)
{
	char	*new_str;
	int		byte_read;

	byte_read = 1;
	while ((!ft_strchr(str, '\n')) && byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		if (byte_read == 0)
		{
			free(buf);
			return (str);
		}
		buf[byte_read] = '\0';
		new_str = str;
		str = ft_strjoin(str, buf);
		free(new_str);
	}
	free(buf);
	return (str);
}

void	remove_first_line(char *str[], int fd)
{
	size_t	i;
	char	*n_str;

	i = 0;
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	if (str[fd][i] == '\n')
		i++;
	if (!str[fd][i])
	{
		free(str[fd]);
		str[fd] = NULL;
		return ;
	}
	n_str = ft_strdup(str[fd] + i);
	free(str[fd]);
	if (!n_str)
		return ;
	str[fd] = n_str;
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str[1024];
	char		*n_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	str[fd] = read_chunks(fd, buf, str[fd]);
	if (!str[fd])
		return (NULL);
	n_str = strdup_to_newline(str[fd]);
	remove_first_line(str, fd);
	return (n_str);
}
