#ifndef GET_NEXT_LINE_H//if not defined
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
//BUFFER_SIZE (1024 bytes) is used to read data from a file in chunks
#endif

#include <fcntl.h>   // for open
#include <unistd.h>  // for read, close
#include <stdlib.h>  // for malloc, free
#include <stdio.h>   // for printf, perror
#include <string.h>  // for strlen
# include <limits.h>


char *get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char    *ft_strdup(const char *s);

#endif
