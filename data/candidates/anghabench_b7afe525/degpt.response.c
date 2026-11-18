/*
 * Increment a value within a circular buffer of a given size.
 *
 * This function calculates the next index in a circular buffer by adding 1
 * to the current value and applying a bitwise AND with (size - 1).
 * This operation effectively wraps the index around to 0 when it reaches
 * the buffer size, assuming 'size' is a power of two.
 *
 * Parameters:
 *   val   - The current index or value to increment.
 *   size  - The size of the circular buffer (must be a power of two).
 *
 * Returns:
 *   The incremented index, wrapped around to 0 if it exceeds or equals 'size'.
 */
int mt76_incr(int current_index, int buffer_size)
{
    return (current_index + 1) & (buffer_size - 1);
}