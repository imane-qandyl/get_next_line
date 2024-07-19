#include "get_next_line.h"

char	*strdup_to_newline(char *str)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	char *res = (char *)malloc(sizeof(char) * (i + 2)); // include null terminator and \n
	if (!res)
		return (NULL);
	while (j <= i) {
        res[j] = str[j];
        j++;
    }
	res[j] = '\0';
    return res;
}
// Function to read file data into a buffer
char	*read_chunks(char *str, int fd)
{
	char temp[BUFFER_SIZE + 1]; //automatically allocated on the stack

	int byte_read = 1;

    while (!ft_strchr(str, '\n') && byte_read != 0) {
        byte_read = read(fd, temp, BUFFER_SIZE);
        if (byte_read == -1) { // 0 if the end of the file is reached, or -1 if an error occurs.
            free(str);
            return NULL;
        }
        temp[byte_read] = '\0';
        char *new_str = ft_strjoin(str, temp);//This ensures that all previously read data and the new data chunk are combined into a single string.
		free(str);
        str = new_str;
		if (!str)
            return NULL;
    }
    return str;
}
// Function to remove the first line from the buffer
char	*remove_full_line(char *str)
{
	int		i;
	int		k;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (NULL);
	char *new = (char *)malloc(ft_strlen(str) - i);
	if (!new)
		return (NULL);
	k = 0;
	i++; // skip the newline character
	while (str[i])
		new[k++] = str[i++];
	new[k] = '\0';
	free(str);
	return new;
}

char *get_next_line(int fd) {
    static char *str;
    char *res;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX) // failure to open the file
        return NULL;
    str = read_chunks(str, fd);
    if (!str)
        return NULL;
    res = strdup_to_newline(str);
    str = remove_full_line(str);
    return res;
}
int main()
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 1;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
/*
The read_file_buffer function reads chunks of data from the file until it encounters a newline character or reaches the end of the file.
The strdup_to_newline function creates a new string containing the characters up to and including the first newline character.
The remove_full_line function updates the static buffer to remove the line that was just read, preparing it for the next call to get_next_line.*/