/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imqandyl <imqandyl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:24:35 by imqandyl          #+#    #+#             */
/*   Updated: 2024/07/22 13:58:16 by imqandyl         ###   ########.fr       */
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

char	*remove_first_line(char *str)
{
	size_t	i;
	char	*n_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	n_str = ft_strdup(str + i);
	free(str);
	if (!n_str)
		return (NULL);
	return (n_str);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;
	char		*n_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	str = read_chunks(fd, buf, str);
	if (!str)
	{
		return (NULL);
	}
	n_str = strdup_to_newline(str);
	str = remove_first_line(str);
	return (n_str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
