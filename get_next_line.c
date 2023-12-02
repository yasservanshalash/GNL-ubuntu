#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char *get_next_line(int fd)
{
    char *line;
    static char *leftover = NULL;
    int i = 0;
    int j = 0;
    int read_chars;

    if (fd < 0)
        return NULL;

    line = calloc(BUFFER_SIZE + 1, sizeof(char));
    memset(line, 0, BUFFER_SIZE + 1);
    if (line == NULL)
        return NULL;

    // Process leftover from previous reads
    if (leftover != NULL)
    {
        while (leftover[j] != '\n' && leftover[j] != '\0')
        {
            line[i++] = leftover[j++];
        }

        if (leftover[j] == '\n')
        {
            char *temp = strdup(leftover + j + 1);
            free(leftover);
            leftover = temp;
            line[i++] = '\n';
            line[i] = '\0';
            return line;
        }

        free(leftover);
        leftover = NULL;
    }

    // Read new data
    read_chars = read(fd, line + i, BUFFER_SIZE - i);
    while (read_chars > 0)
    {
        i += read_chars;

        if (strchr(line, '\n'))
        {
            j = i - read_chars; // Update j to the beginning of the current chunk

            while (j < i && line[j] != '\n')
            {
                j++;
            }

            if (j < i)
            {
                leftover = strdup(line + j + 1);
                line[j++] = '\n';
                line[j] = '\0';
                return line;
            }
        }

        // Extend the buffer
        char *temp = realloc(line, (i + BUFFER_SIZE + 1) * sizeof(char));
        if (temp == NULL) {
            free(line);
            return NULL;
        }
        line = temp;
        memset(line + i, 0, BUFFER_SIZE + 1);

        // Read more data
        read_chars = read(fd, line + i, BUFFER_SIZE);
    }

    // Handle end of file or error
    if (i > 0)
    {
        line[i] = '\0';
        return line;
    }
    else
    {
        free(line);
        return NULL;
    }
}


// int main(void)
// {
//     int fd;

//     fd = open("text.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));

//     close(fd);
//     return (0);
// }