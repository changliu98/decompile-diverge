int shm_detach(void *shmaddr)
{
  return shmdt(shmaddr);
}