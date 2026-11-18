Optimized for reverse engineering readability
int __cdecl mustache_buffer_insert(MUSTACHE_BUFFER *buf, off_t off, const void *data, size_t n)
{
  uint8_t *realloc_ptr;
  size_t new_alloc;

  // Check if the current buffer has enough space for the new data
  if (n + buf->n > buf->alloc)
  {
    // Double the required capacity to minimize future reallocations
    new_alloc = 2 * (n + buf->n);
    realloc_ptr = (uint8_t *)realloc(buf->data, new_alloc);
    
    // Bail out if memory allocation fails
    if (!realloc_ptr)
      return -1;
      
    buf->data = realloc_ptr;
    buf->alloc = new_alloc;
  }

  // If inserting in the middle, shift existing data to the right to make room
  if (off < buf->n)
    memmove(&buf->data[off + n], &buf->data[off], buf->n - off);

  // Copy the new data into the requested offset
  memcpy(&buf->data[off], data, n);

  // Update the total size of the buffer
  buf->n += n;
  
  return 0;
}