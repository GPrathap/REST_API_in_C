#pragma once

#include <stdint.h>
#include <stdbool.h>
/**
* @param		len   current length of buffer (used bytes)
 * @param       limit maximum length of buffer (allocated)
 * @param		data  insert bytes here
*/
typedef struct
{
    size_t len;
    size_t limit;
    uint8_t *data;
} buf_t;

/**
 * buf_size create buffer for given size
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       len   length of  string to be saved
 */
buf_t * buf_size(buf_t *buf, size_t len);
/**
 * buf_push adding characters to buffer
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       c     a character
 */
void buf_push(buf_t *buf, uint8_t c);

/**
 * buf_push adding characters to buffer
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 * @param       data  character array
 */
void buf_concat(buf_t *buf, uint8_t *data, size_t len);

/**
 * buf_tostr    convert buffer struct into a string
 * @param		buf   is the struct which includes length of buffer,limit of the buffer and char array
 */
char * buf_tostr(buf_t *buf);



