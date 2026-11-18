/**
 * Performs an atomic bitwise OR operation on the value pointed to by v1.
 *
 * @param v1 Pointer to the unsigned long value to be updated.
 * @param v2 The unsigned long value to OR with the current value of *v1.
 */
void atomic_or_long(unsigned_long *target, unsigned_long value)
{
    // Update the value at v1 by performing a bitwise OR with v2
    *target |= value;
}