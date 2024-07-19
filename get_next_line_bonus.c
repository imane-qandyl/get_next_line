#include "get_next_line_bonus.h"

char *strdup_to_newline(char *str) {
    int i = 0;
    int j = 0;

    if (!str || ft_strlen(str) == 0)
        return NULL;
    while (str[i] && str[i] != '\n')
        i++;
    char *res = (char *)malloc(sizeof(char) * (i + 2)); // include null terminator and \n
    if (!res)
        return NULL;
    while (j <= i) {
        res[j] = str[j];
        j++;
    }
    res[j] = '\0';
    return res;
}

// Function to read file data into a buffer
void read_chunks(char *str[], int fd) {
    char *temp;
    int byte_read = 1;

    temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (temp == NULL)
        return;
    while (!ft_strchr(str[fd], '\n') && byte_read != 0) {
        byte_read = read(fd, temp, BUFFER_SIZE);
        if (byte_read == -1) { // 0 if the end of the file is reached, or -1 if an error occurs.
            free(temp);
            str[fd] = NULL;
            return;
        }
        temp[byte_read] = '\0';
        char *new_str = ft_strjoin(str[fd], temp); // This ensures that all previously read data and the new data chunk are combined into a single string.
        free(str[fd]);
        str[fd] = new_str;
        if (!str[fd])
            return;
    }
    free(temp);
}

// Function to remove the first line from the buffer
void remove_full_line(char *str[], int fd) {
    int i = 0;
    int k = 0;

    while (str[fd][i] && str[fd][i] != '\n')
        i++;
    if (!str[fd][i]) {
        free(str[fd]);
        str[fd] = NULL;
        return;
    }
    char *new = (char *)malloc(ft_strlen(str[fd]) - i);
    if (!new)
        return;
    i++; // skip the newline character
    while (str[fd][i])
        new[k++] = str[fd][i++];
    new[k] = '\0';
    free(str[fd]);
    str[fd] = new;
}

char *get_next_line(int fd) {
    static char *str[1024]; // Array to store buffers for multiple file descriptors
    char *res;

    if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX) // Failure to open the file or invalid buffer size
        return NULL;
    read_chunks(str, fd);
    if (!str[fd])
        return NULL;
    res = strdup_to_newline(str[fd]);
    remove_full_line(str, fd);
    return res;
}

int main() {
    int fd[3]; // Array to store file descriptors
    char *line;
    int i = 0;

    // Open files with file descriptors 3, 4, and 5
    fd[0] = open("file.txt", O_RDONLY);
    fd[1] = open("file1.txt", O_RDONLY);
    fd[2] = open("file2.txt", O_RDONLY);

    if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1) {
        perror("Error opening file");
        return 1;
    }

    while( i < 3) {
        printf("Reading from file descriptor %d:\n", fd[i]);
        while ((line = get_next_line(fd[i])) != NULL) {
            printf("%s\n", line);
            free(line);
        }
        close(fd[i]);
        i++;
    }

    return 0;
}
/*why start from 3
File descriptors 0, 1, and 2 are reserved for standard input, standard output, and standard error
*/