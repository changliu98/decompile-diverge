size_t func0(char **tuple, size_t size) {
    size_t total_size = 0;
    for (size_t i = 0; i < size; i++) {
        total_size += sizeof(char*);
    }
    return total_size;
}