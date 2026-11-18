long shmDetach(void *sharedMemoryAddress)
{
 return (long)shmdt(sharedMemoryAddress);
}