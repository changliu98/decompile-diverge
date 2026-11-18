int __cdecl try_enlarge(RespResponse *r, uint32_t add_size)
{
  char *new_buf;
  uint32_t required_size;
  uint32_t new_capacity;

  // Calculate the total required buffer size
  required_size = r->used_size + add_size;

  // Find the next power-of-two capacity that fits the required size
  new_capacity = r->buf_size;
  while (new_capacity < required_size) {
    new_capacity *= 2;
  }

  // Attempt to reallocate the buffer to the new capacity
  new_buf = (char *)realloc(r->buf, new_capacity);
  if (!new_buf)
    return -1;

  // Update the response structure with the new buffer and capacity
  r->buf = new_buf;
  r->buf_size = new_capacity;
  
  return 0;
}