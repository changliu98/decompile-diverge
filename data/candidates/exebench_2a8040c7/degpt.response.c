/**
 * Detaches a shared memory segment from the calling process's address space.
 *
 * @param addr Pointer to the address where the shared memory segment is attached.
 * @return Returns 0 on success, or -1 on error (with errno set appropriately).
 *         Casts the return value of shmdt to long for consistency.
 */
long shmDetach(float *shared_memory_address)
{
  return (long)shmdt(shared_memory_address);
}