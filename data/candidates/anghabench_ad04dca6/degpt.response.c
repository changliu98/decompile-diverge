/*
 * Calculate the CPU core index for a given thread.
 *
 * Parameters:
 *   cpu - The logical CPU number (thread ID).
 *
 * Returns:
 *   The index of the CPU core that the thread belongs to.
 *
 * Logic:
 *   Shift the cpu number right by threads_shift bits to isolate the core index.
 *   The threads_shift value is cast to byte and masked with 0x1f to ensure
 *   the shift amount is within the valid range (0-31) for a 32-bit integer.
 */
int cpu_core_index_of_thread(int thread_id)
{
    return thread_id >> ((byte)threads_per_core_shift & 0x1f);
}