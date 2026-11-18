int shmDetach(void *shmaddr)
{
  return shmdt(shmaddr);
}