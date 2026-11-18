void *mrbc_raw_realloc(void *ptr, unsigned int size) {
    void *ret_val = NULL;

    // If ptr is not NULL and size is 0, behave like free()
    if (ptr != NULL && size == 0) {
        mrbc_raw_free(ptr);
        return NULL;
    }

    void *pool = memory_pool;
    unsigned int *hdr = (unsigned int *)((char *)ptr - 4);

    // Calculate required block size: size + 4 (header), aligned to 4 bytes, min 32
    unsigned int req_size = size + 4;
    req_size = (req_size + 3) & ~3;
    if (req_size < 32) {
        req_size = 32;
    }

    // Get current block size from header (lower 24 bits, already 4-byte aligned)
    unsigned int curr_size = (*hdr & 0xFFFFFF) & ~3;

    if (req_size > curr_size) {
        // Need to expand. Check if the next block is free and can be merged.
        unsigned int *next_hdr = (unsigned int *)((char *)hdr + curr_size);

        if ((*next_hdr & 0xFFFFFF & 1) == 0) { // Next block is free
            if (curr_size + (*next_hdr & 0xFFFFFF & ~3) >= req_size) {
                // Merge with next block
                remove_free_block(pool, next_hdr);
                merge_block(hdr, next_hdr);
            }
        }
    }

    // Re-evaluate current size after potential merge
    curr_size = (*hdr & 0xFFFFFF) & ~3;
    unsigned int *next_hdr = (unsigned int *)((char *)hdr + curr_size);

    // Try to split the block if it's too large
    unsigned int *rem_hdr = split_block(hdr, req_size);

    if (rem_hdr != NULL) {
        // Successfully split. Mark the remainder block as free and add to free list.
        *rem_hdr = (*rem_hdr & 0xFF000000) | ((*rem_hdr & 0xFFFFFF) | 2);
        
        if ((*next_hdr & 0xFFFFFF & 1) == 0) { // If the block after remainder is also free
            remove_free_block(pool, next_hdr);
            merge_block(rem_hdr, next_hdr);
        } else {
            // Clear the 'in_use' bit (bit 1) for the remainder block
            *rem_hdr = (*rem_hdr & 0xFF000000) | ((*rem_hdr & 0xFFFFFF) & ~2);
        }
        
        add_free_block(pool, rem_hdr);
        ret_val = ptr;
    } else {
        // Could not split (either block is exactly the right size or too small to split)
        // Mark the current block as in-use
        *next_hdr = (*next_hdr & 0xFF000000) | ((*next_hdr & 0xFFFFFF) | 2);
        ret_val = ptr;
    }

    // If we couldn't expand in place (ret_val is still NULL), allocate new memory
    if (ret_val == NULL) {
        void *new_ptr = mrbc_raw_alloc(size);
        if (new_ptr == NULL) {
            return NULL;
        }

        // Copy data from old block to new block
        unsigned int copy_size = curr_size - 4;
        memcpy(new_ptr, ptr, copy_size);

        // Copy VM ID (highest byte of the header)
        unsigned char vm_id = (*hdr >> 24) & 0xFF;
        mrbc_set_vm_id(new_ptr, vm_id);

        // Free the old block
        mrbc_raw_free(ptr);
        
        ret_val = new_ptr;
    }

    return ret_val;
}