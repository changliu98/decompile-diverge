// Sets all output parameters to -1, indicating that mallinfo information is not available.
void clib_mallinfo(long *total_system_allocated, long *heap_free_bytes, long *total_allocated_space, long *total_free_space, long *used_memory, long *available_memory)
{
    *total_system_allocated = -1;      // Total non-mmapped bytes allocated from system
    *heap_free_bytes = -1;     // Total bytes in heap free blocks
    *total_allocated_space = -1;    // Total allocated space (equivalent to uordblks + fordblks)
    *total_free_space = -1;    // Total free space (not necessarily contiguous)
    *used_memory = -1;   // Total allocated space (used memory)
    *available_memory = -1;   // Total free space (available memory)
}