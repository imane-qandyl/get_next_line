/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:24:35 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/31 16:59:20 by imqandyl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	n_str = (char *)malloc(i + 1);
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

char	*read_chunks(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	byte_read = 1;
	while (!ft_strchr(str) && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(str);
			return (NULL);
		}
		buffer[byte_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	return (str);
}

char	*remove_first_line(char *str[], int fd)
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
		return (NULL);
	}
	n_str = ft_strdup(str[fd] + i);
	free(str[fd]);
	str[fd] = NULL;
	if (!n_str)
		return (NULL);
	return (n_str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*n_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_chunks(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	n_str = strdup_to_newline(str[fd]);
	if (!n_str)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = remove_first_line(str, fd);
	return (n_str);
}
