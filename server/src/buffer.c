/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** buffer
*/

#include <assert.h>
#include "server.h"

char *append_buffer(char *dst, char src[BUFFER_SIZE],
    size_t *dst_len, size_t src_len)
{
    dst = realloc(dst, *dst_len + src_len);
    memcpy(dst + *dst_len, src, src_len);
    *dst_len += src_len;
    return dst;
}

char *slice_buffer(char **buffer, size_t *buffer_size, size_t bytes)
{
    char *slice = NULL;

    if (bytes > *buffer_size)
        return NULL;
    slice = malloc(bytes);
    assert(slice);
    memmove(slice, *buffer, bytes);
    memmove(*buffer, *buffer + bytes, *buffer_size - bytes);
    *buffer_size -= bytes;
    if (*buffer_size == 0) {
        free(*buffer);
        *buffer = NULL;
    } else
        *buffer = realloc(*buffer, *buffer_size);
    return slice;
}

char *get_packet(char **buffer, size_t *buffer_size)
{
    char *tmp = memchr(*buffer, '\n', *buffer_size);
    char *packet = NULL;
    size_t offset = tmp - *buffer;

    if (tmp == NULL)
        return NULL;
    packet = slice_buffer(buffer, buffer_size, offset + 1);
    packet[offset] = '\0';
    return packet;
}
