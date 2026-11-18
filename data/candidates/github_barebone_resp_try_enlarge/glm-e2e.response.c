int try_enlarge(struct buffer *buf, unsigned int additional_size) {
    unsigned int new_capacity = buf->capacity;
    
    // Double the capacity until it's large enough to hold the new size
    while (new_capacity < buf->size + additional_size) {
        new_capacity <<= 1; // Equivalent to new_capacity *= 2
    }
    
    void *new_data = realloc(buf->data, new_capacity);
    if (new_data == NULL) {
        return -1;
    }
    
    buf->data = new_data;
    buf->capacity = new_capacity;
    
    return 0;
}