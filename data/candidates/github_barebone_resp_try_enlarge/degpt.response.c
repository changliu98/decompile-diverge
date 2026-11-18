int try_enlarge(RespResponse *response, uint32_t additional_bytes)
{
    // Calculate the new buffer size, starting from the current size
    uint32_t target_buffer_size = response->buf_size;
    
    // Double the buffer size until it is large enough to hold the current used data plus the additional required size
    while (target_buffer_size < response->used_size + additional_bytes) {
        target_buffer_size <<= 1;
    }
    
    // Attempt to reallocate the buffer to the new size
    char *new_buffer_ptr = realloc(response->buf, (ulong)target_buffer_size);
    
    // Check if reallocation failed
    if (new_buffer_ptr == NULL) {
        return -1;
    }
    
    // Update the buffer pointer and size in the response structure
    response->buf = new_buffer_ptr;
    response->buf_size = target_buffer_size;
    
    // Return success
    return 0;
}