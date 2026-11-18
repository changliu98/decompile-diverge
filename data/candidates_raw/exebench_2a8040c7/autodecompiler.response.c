long detachFromSharedMemory(void *sharedMemoryAddress)
{
 return (long)shmdt(sharedMemoryAddress);
}